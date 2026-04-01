---
description: Backup file-level guidance for exercise files when task.cpp, SUMMARY.md, or feladat.pdf are edited outside the dedicated exercise solver agent.
applyTo: "**/{task.cpp,SUMMARY.md,feladat.pdf}"
---

# Exercise File Guidance

This file is a lightweight fallback for direct exercise file edits.

The canonical end-to-end batch workflow lives in `.github/agents/exercise-batch-solver.agent.md`.

- `task.cpp` should start with a Hungarian solution explanation comment.
- Immediately after the explanation, include one or more exercise-specific hints in this format:
   `Hint 1: || ... ||`
   `Hint 2: || ... ||`
   `Hint 3: || ... ||`
- Continue the numbering sequentially if more hints are needed.
- Use as many hints as the exercise complexity justifies. Do not pad with filler hints.
- Never use placeholder hint text.
- `SUMMARY.md` should use the educational table format `| # | Feladat | Kategória | Röviden használt módszer / algoritmus | Nehézség | Órai cél | Állapot |`, include the short batch note and scale section, and stay numerically ordered.
