# Notepad

## Console-Based Notepad Application

This repository contains a **console-based notepad application** developed as a Data Structures course project at the National University of Computer & Emerging Sciences (NUCES), Islamabad (Fall 2024). It implements a functional text editor with advanced features like **custom undo/redo**, **search**, **word and sentence completion**, and more—**without STL or standard arrays**, emphasizing **dynamic memory structures**.

---

## 🧠 Core Concepts

- **2D Linked List**: Stores characters with connections in all directions (up, down, left, right).
- **N-Ary Tree**: For word search and word completion.
- **Chilli Milli Tree**: For sentence prediction and completion.
- **Custom Stack and Circular Buffer**: For undo functionality and cursor tracking.
- **No STL or built-in containers**: All data structures (linked list, stack, queue, trees) are implemented from scratch.

---

## ✨ Features

### 📝 Text Editing
- Insert characters (`A-Z`, `a-z`, space) with automatic wrapping.
- Supports up to 18 lines and 100 characters per line.
- Handles `Enter` for new lines and `Backspace` for character deletion.
- Real-time character display with colored output using `Windows.h`.

### ⌨️ Keyboard Shortcuts
| Action                     | Key                          |
|----------------------------|------------------------------|
| Move cursor                | Arrow keys                   |
| Insert new line            | `Enter`                      |
| Delete character           | `Backspace`                  |
| Save file                  | `Ctrl` key                   |
| Exit                       | `Esc`                        |
| Search                     | `1`                          |
| Word completion            | `@` (after word)             |
| Sentence completion        | `*` (after space)            |
| Undo                       | `Alt`                        |
| View N-Ary tree            | `2`                          |
| View ChilliMilli tree      | `3`                          |
|----------------------------|------------------------------|

---

### 🔄 Undo (via `Alt`)
- Undoes the **last word insertion**.
- Tracks up to **5 words** using a **circular buffer** (custom class `Values`) and a `Stack`.
- Automatically deletes all characters in a word in reverse.

### 💾 File Operations
- Create new file: Enter a name and start editing.
- Load file: Automatically loads text from a `.txt` file into the editor.
- Save file: Press `Ctrl` or say "Yes" when prompted on exit.
- Exit: `Esc` key prompts save before quitting.

### 🔍 Searching
- Press `1`, input a word.
- Uses an **N-ary tree** for fast searching (case-insensitive).
- Displays line number if found.

### 🔡 Word Completion (via `@`)
- Based on **N-ary tree**.
- Suggests words matching the typed prefix.
- Suggestions displayed to the right for selection.

### ✏️ Sentence Completion (via `*`)
- Uses a **ChilliMilli tree** to suggest sentence continuations.
- Based on previously typed sentence fragments.

---

## ⚙️ How to Run

1. Clone this repository.
2. Open `Source.cpp` in **Visual Studio 2022** or another Windows-compatible C++ compiler.
3. Compile and run.
4. Follow the on-screen menu or use key bindings.

---

## 🔐 Notes
- Designed to work in **Windows console only** (`<Windows.h>` used).
- Handles edge cases: full buffer, end of line, empty search results.
- Does not use STL containers (`std::vector`, `std::stack`, etc. not allowed).

---

## 👨‍💻 Author
**Hanzlah Mehmood Ch**

---

## ✅ Example Use Cases
- Fast typing and suggestion experience in CLI
- Undo accidental words
- Educational project to learn custom data structures

---
