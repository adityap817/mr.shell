# Mr.Shell by adiicodes

**An advanced, colorful command-line interpreter written in C++**

---

## Overview

Shell++ is a custom command-line shell implemented in C++ that aims to provide an engaging, interactive terminal experience with advanced features beyond a basic shell. It supports:

- Colorful, dynamic prompts with fun sentences and emojis  
- Built-in commands like `cd`, `help`, `motivate` (inspirational quotes), `time` (show current time), and `exit`  
- Translation of simple English phrases to shell commands (e.g., "list files" → `ls`)  
- Background execution of commands (using `&` suffix)  
- Easy extensibility for adding new built-in commands  
- No command history tracking (for privacy and simplicity)

---

## Features

| Feature                   | Description                                             |
|---------------------------|---------------------------------------------------------|
| Colorful Prompt           | Displays a vibrant prompt with motivational sentences.  |
| English-to-Command Mapping| Type common phrases like "go home" instead of `cd ~`.   |
| Background Jobs           | Run commands in the background with `&` at the end.     |
| Built-in Commands         | Includes `cd`, `exit`, `help`, `motivate`, `time`.      |
| Simple & Clean UI         | Minimal dependencies, clear color coding for readability.|

---

## Built-in Commands

- `cd [dir]` — Change the current working directory  
- `exit` — Exit the shell  
- `help` — Show list of built-in commands  
- `motivate` — Display a random motivational quote  
- `time` — Show current system time  

---

## Example Usage

```bash
Mr. Shell 😎 > Ready to hack the planet! >
> list files
file1.cpp  file2.h  README.md

Mr. Shell 😎 > Your wish is my command. >
> motivate
Keep pushing forward! 🚀

Mr. Shell 😎 > What shall we do next? >
> ls &
[1] 12345
✔
