# MarkOut
> *"Spot the changes that matter — skip the clutter."*  

**MarkOut** is a lightweight, fast CLI tool that helps you **identify and highlight changes** between two files.  
It skips irrelevant lines (empty lines, comments) and highlights actual differences **in red** for easy spotting.  

##  Features

-  **Line-by-line comparison** between two files.
-  **Easy CLI usage** – Compare files with a single command.
-  **Ignores noise**:
  - Empty lines
  - Single-line comments (`//`)
  - Multi-line comments (`/* ... */`)
-  **Highlights changes in red** for quick identification.
-  **Fast**: Written in C++ for high performance.
-  **Tested**: Includes RSpec tests for binary behavior.

---

## Installation

```bash
# Clone the repository
git clone https://github.com/yourusername/MarkOut.git

# Go into the directory
cd MarkOut

# Build the binary
make

# Install globally (requires sudo)
sudo install diff /usr/local/bin/differentiate

---
```
## Usage
```bash
differentiate {file1 address} {file2 address}

Example
> differentiate src/trial.cpp downloads/trial_new.cpp
```

Thanks !



