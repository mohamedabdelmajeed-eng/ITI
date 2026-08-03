# Assignment 4 - Customize Your Linux Terminal

## Overview

This assignment customizes the Bash terminal by creating custom commands (functions) that can be used in every terminal session.

The functions were added to the `~/.bashrc` file and activated using:

```bash
source ~/.bashrc
```

---

## Implemented Commands

### 1. print_content

Displays the contents of the current directory.

**Usage**

```bash
print_content
```

---

### 2. go_to

Changes the current working directory.

**Usage**

```bash
go_to <directory>
```

**Example**

```bash
go_to ~/Projects
```

---

### 3. search

Searches for a keyword inside a file and highlights the matching text.

**Usage**

```bash
search "keyword" filename
```

**Example**

```bash
search "hello" test.txt
```

---

### 4. show_file

Displays the contents of a file with line numbers.

**Usage**

```bash
show_file filename
```

**Example**

```bash
show_file test.txt
```

---

### 5. remove

Deletes a file after asking for confirmation.

**Usage**

```bash
remove filename
```

**Example**

```bash
remove test.txt
```

---

### 6. make_dir

Creates a complete directory hierarchy.

**Usage**

```bash
make_dir directory_path
```

**Example**

```bash
make_dir project/src/include
```

---

### 7. create_file

Creates an empty file.

**Usage**

```bash
create_file filename
```

**Example**

```bash
create_file notes.txt
```

---

## Files

- `README.md`
- Screenshots demonstrating each command (if required)

## Conclusion

All required Bash functions were successfully implemented inside the `~/.bashrc` file. After reloading the Bash configuration using `source ~/.bashrc`, the custom commands became available in every new terminal session.