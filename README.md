# Notepad
# Console-Based Notepad Application

This repository contains a console-based notepad application developed for the Data Structures course at the National University of Computer & Emerging Sciences (NUCES), Islamabad, for Fall 2024. The project implements a fully functional text editor with advanced features like text manipulation, undo/redo, searching, and word/sentence completion, all built using custom data structures.

## Project Overview
- **Description**: A text editor that uses a 2D linked list for character storage, an N-ary tree for efficient searching and word completion, and a Chilli Milli tree for sentence suggestions. No arrays or STL are allowed, emphasizing dynamic memory management and custom implementations.
- **Features**:
  - **Text Editing**: Insert text (alphabets only) character-by-character with word wrapping, line breaks, and cursor navigation. Delete characters with backspace, shifting text accordingly.
  - **Undo/Redo**: Tracks up to 5 recent word-level actions using stacks for reversal and restoration.
  - **File Operations**: Create, load, save, and exit. Press `Esc` to exit; the program prompts "Yes" to save to a `.txt` file or "No" to exit without saving.
  - **Searching**: Case-insensitive search with a time complexity of ≤ 1.5*log(n) using an N-ary tree. Press `1` to search for a string, highlights matches in the text, and displays line numbers in the search area.
  - **Word Completion**: Suggests words based on prior input using the N-ary tree (O(n) complexity). Press `Shift + @` to request suggestions, displayed in the suggestions area for keyboard selection.
  - **Sentence Completion**: Suggests frequent follow-up words using a Chilli Milli tree (O(n) complexity). Press `Shift + *` to request sentence completion, enhancing user input efficiency.
  - **Window Layout**: 60% main text area, 20% suggestions area, 20% search area.

## How to Run
1. Clone the repository.
2. Open the `source.cpp` file in any editor like Visual Studio 2022.
3. Compile and run the program.
4. Use the menu to create/load files, edit text, and access features with the following key bindings:
   - `Esc`: Exit (prompts "Yes" to save the file or "No" to exit).
   - `1`: Search for a string.
   - `Shift + @`: Request word completion suggestions.
   - `Shift + *`: Request sentence completion suggestions.

## Notes
- Additional key mappings (e.g., save (ctrl), undo (alt)) are intuitive and documented in the code comments.
- Thoroughly tested for edge cases like empty files, large inputs, and invalid operations.
- The `main()` function demonstrates all features, including text editing, searching, and completions.

## Author
- Hanzlah Mehmood Ch
