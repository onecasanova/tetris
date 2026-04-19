# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build and Run

```bash
gcc tetris.c -o tetris -lncurses
./tetris
```

Press `q` to quit the game.

## Architecture

Single-file C program (`tetris.c`) using ncurses for terminal rendering.

**Global state:**
- `board[ROWS][COLS]` — 2D int array representing locked cells (0 = empty, 1 = filled)
- `shapes[PCS][4][4]` — 3D array storing all 7 tetromino shapes as 4x4 matrices. Rotation mutates these arrays in-place (destructive — the original shape is permanently modified on each rotation)
- `current` — global `struct Piece` with `type`, `row`, `col`, `rot` fields

**Game loop (`main`):** Non-blocking ncurses input via `nodelay`. Gravity is time-based using `clock()` and `G_TIME` (0.5s). Each iteration: handle gravity → handle input → `draw_board()` + `draw_piece()` → `refresh()`.

**Key functions:**
- `collision(p_row, p_col, type)` — checks proposed position against walls and occupied board cells; used before every move/rotate
- `lock_piece()` → `line_clear()` → `spawn_piece()` — called when a piece can't fall further
- `rotate_clock()` / `rotate_cclock()` — implemented as transpose + row-reverse operations directly on `shapes[current.type]`

## What's Left (from plan.txt)

- Scoring and game over detection (spawn collision = game over)
- Polish: next piece preview, levels, speed increase

## Known Issues / Notes

- Rotation mutates `shapes[]` globally, so a piece that has been rotated changes its stored shape permanently. This works for single-player but is worth understanding.
- `current.rot` field was removed — rotation state is implicit in the mutated shape data, so tracking it separately isn't meaningful with this design.
- Up/Down arrow keys currently rotate (not move up/down); spacebar soft-drops one row.
