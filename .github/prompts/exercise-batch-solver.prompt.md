---
name: exercise-batch-solver
description: Start a full exercise batch run from a folder and a numbered range, and keep the agent going until the last requested exercise is solved.
---

You are working in the repository at /home/peocz/Projects/MyMesterAlphaMester.

Use the `exercise-batch-solver` agent as the source of truth for the exercise workflow. Do not restate or weaken it.

Batch-specific launch rules:
- Solve the full requested numeric range end-to-end. Do not stop at a partial range.
- The parent agent owns code acceptance, validation, `SUMMARY.md`, and the final audit.
- Use subagents only as bounded support. Do not let them be the sole owner of a finished exercise without a parent re-check.
- Completion is invalid until the full-range audit passes and the run ends with a brief summary plus `task_complete`.

Required audit before stop:
- Statement checked for every requested exercise.
- Solution file present for every requested exercise.
- Explanation comment present and hint block present for every requested `task.cpp`.
- Compilation and sample validation completed when available.
- Time limits used for compile, sample, brute-force, and diagnostic commands.
- `SUMMARY.md` fully covers the requested range in the required table format.

Suggested user input template:
- Folder: Haladó/Kombinatorikai algoritmusok
- Range: 21-40
- Special notes: use subagents only when they materially help, do not stop early, and keep the summary table complete for the whole range.
