#!/bin/bash

# 1. PATH RESOLUTION
AGENT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$AGENT_DIR")"
cd "$PROJECT_ROOT" || { echo "Failed to navigate to project root"; exit 1; }

TASKS_FILE="$AGENT_DIR/tasks.json"

if [ ! -f "$TASKS_FILE" ]; then
    echo "Error: Could not find tasks.json at $TASKS_FILE"
    exit 1
fi

# 2. THE PROPER LOOP (Using 'while read' to avoid space-splitting errors)
jq -c '.tasks[]' "$TASKS_FILE" | while read -r task_data; do
    
    # Extract Settings
    name=$(echo "$task_data" | jq -r '.name // "Unnamed Task"')
    prompt=$(echo "$task_data" | jq -r '.prompt // ""')
    agent=$(echo "$task_data" | jq -r '.agent // ""')
    model=$(echo "$task_data" | jq -r '.model // ""')
    reasoning=$(echo "$task_data" | jq -r '.reasoning // ""')
    approval=$(echo "$task_data" | jq -r '.approval_mode // "autopilot"')
    
    # Extract Evaluator Settings
    eval_agent=$(echo "$task_data" | jq -r '.evaluator.agent // ""')
    eval_model=$(echo "$task_data" | jq -r '.evaluator.model // ""')
    eval_prompt=$(echo "$task_data" | jq -r '.evaluator.prompt // ""')

    echo "====================================================="
    echo "🤖 Starting Task: $name"
    
    # 3. BUILD SOLVER FLAGS USING BASH ARRAYS (Safest method for strings)
    solver_args=()
    
    if [ "$approval" == "autopilot" ]; then 
        solver_args+=( "--allow-all-tools" )
    fi
    
    if [ "$agent" != "null" ] && [ ! -z "$agent" ]; then 
        solver_args+=( "--agent" "$agent" )
    fi
    
    if [ "$model" != "null" ] && [ ! -z "$model" ]; then 
        solver_args+=( "--model" "$model" )
    fi
    
    if [ "$reasoning" != "null" ] && [ ! -z "$reasoning" ] && [ "$reasoning" != "false" ]; then 
        solver_args+=( "--reasoning-effort" "$reasoning" )
    fi
    
    # 4. RUN THE SOLVER
    # The "${solver_args[@]}" injects the flags perfectly formatted
    copilot "${solver_args[@]}" -p "$prompt"
    
    # 5. THE AI EVALUATION LOOP
    if [ -z "$eval_prompt" ] || [ "$eval_prompt" == "null" ]; then
        echo "⏭️ No AI evaluator specified. Moving to next task."
        continue
    fi

    max_retries=3
    attempt=0
    
    while [ $attempt -lt $max_retries ]; do
        echo "🧐 QA Agent is evaluating the work..."
        
        # Build Evaluator flags array with --silent for clean stdout
        eval_args=( "--allow-all-tools" "--silent" )
        if [ "$eval_agent" != "null" ] && [ ! -z "$eval_agent" ]; then 
            eval_args+=( "--agent" "$eval_agent" )
        fi
        if [ "$eval_model" != "null" ] && [ ! -z "$eval_model" ]; then 
            eval_args+=( "--model" "$eval_model" )
        fi
        
        # Tell the QA agent to use a specific XML tag
        strict_eval_prompt="$eval_prompt. If all criteria are met, you MUST include the exact string <VERDICT>PASS</VERDICT> in your response. If it fails, explain what is missing, and DO NOT output the verdict tag."
        
        # Run Evaluator
        eval_output=$(copilot "${eval_args[@]}" -p "$strict_eval_prompt" 2>&1)
        
        # Simply grep for the exact XML tag. We don't care about the length or the metadata anymore.
        if echo "$eval_output" | grep -q "<VERDICT>PASS</VERDICT>"; then
            echo "✅ QA Agent strictly approved the changes!"
            break
        else
            echo "❌ QA Agent rejected the changes. Passing feedback..."
            
            fix_prompt="The QA agent reviewed your work and provided this feedback:\n\n$eval_output\n\nPlease fix these issues and save the files."
            
            copilot "${solver_args[@]}" -p "$fix_prompt"
            attempt=$((attempt+1))
        fi
    done
    
    if [ $attempt -eq $max_retries ]; then
        echo "⚠️ Max retries reached for $name. Proceeding to prevent infinite loop..."
    fi
done

echo "🎉 All tasks processed!"