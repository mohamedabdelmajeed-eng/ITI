div align="center">

<img width="100%" src="https://capsule-render.vercel.app/api?type=waving&color=0:0D1117,45:10251B,100:00FF88&height=230&section=header&text=Linux%20Engineering%20Journey&fontSize=48&fontColor=FFFFFF&animation=fadeIn&fontAlignY=38&desc=ITI%20Training%20%E2%80%A2%20Shell%20%E2%80%A2%20System%20Fundamentals%20%E2%80%A2%20Developer%20Workflow&descAlignY=60&descSize=18"/>

# 🐧 Linux Training Portfolio

### Command Line • System Fundamentals • Bash • Developer Workflow

<p>
  <img src="https://img.shields.io/badge/OS-Linux-00FF88?style=for-the-badge&logo=linux&logoColor=white&labelColor=0D1117"/>
  <img src="https://img.shields.io/badge/Shell-Bash-4EAA25?style=for-the-badge&logo=gnubash&logoColor=white&labelColor=0D1117"/>
  <img src="https://img.shields.io/badge/Training-ITI-00C2FF?style=for-the-badge&labelColor=0D1117"/>
  <img src="https://img.shields.io/badge/Focus-System%20Thinking-7C3AED?style=for-the-badge&labelColor=0D1117"/>
</p>

<br/>

<img src="https://skillicons.dev/icons?i=linux,bash,ubuntu,git,github,vscode,cmake,cpp&theme=dark" alt="Linux Development Stack"/>

<br/><br/>

> **A hands-on Linux journey focused on understanding the operating environment, mastering the terminal, and building the system-level confidence required for embedded and automotive software development.**

</div>

---

## ✨ Overview

This folder is part of my **ITI training journey** and focuses on practical Linux usage from a software engineer's perspective.

Linux is more than an operating system in this learning path. It is the environment in which software is **built, executed, inspected, debugged, automated, and integrated**.

The training develops confidence in:

- navigating Linux efficiently,
- working with files and directories,
- understanding users and permissions,
- managing processes,
- using shell tools and pipelines,
- automating repetitive tasks,
- working with development tools,
- and preparing for **Embedded Linux, Qt, and Automotive IVI** projects.

<p align="center">
  <a href="https://github.com/mohamedabdelmajeed-eng/ITI">
    <img src="https://img.shields.io/badge/←%20BACK%20TO%20ITI%20REPOSITORY-0D1117?style=for-the-badge&logo=github&logoColor=white"/>
  </a>
</p>

---

# 🧭 Linux Engineering Roadmap

```text
┌────────────────────────────────────────────────────────────────┐
│                     LINUX ENGINEERING PATH                     │
├────────────────────────────────────────────────────────────────┤
│                                                                │
│  Linux Fundamentals                                            │
│       │                                                        │
│       ▼                                                        │
│  Filesystem & Navigation                                       │
│       │                                                        │
│       ▼                                                        │
│  Users • Groups • Permissions                                  │
│       │                                                        │
│       ▼                                                        │
│  Processes • Services • Resources                              │
│       │                                                        │
│       ▼                                                        │
│  Shell Tools • Pipes • Redirection                             │
│       │                                                        │
│       ▼                                                        │
│  Bash Automation                                               │
│       │                                                        │
│       ▼                                                        │
│  Developer / Embedded / Automotive Workflow                    │
│                                                                │
└────────────────────────────────────────────────────────────────┘
```

---

# 🎯 Core Learning Areas

<table>
<tr>
<td width="50%" valign="top">

### 📂 Filesystem & Navigation

- Linux directory structure
- Absolute vs. relative paths
- File and directory operations
- Search and discovery
- Links
- Mounting concepts
- Disk usage awareness
- File inspection

</td>
<td width="50%" valign="top">

### 🔐 Users & Permissions

- Users and groups
- Ownership
- Read / write / execute permissions
- `chmod`
- `chown`
- Privilege concepts
- `sudo`
- Secure access thinking

</td>
</tr>

<tr>
<td width="50%" valign="top">

### ⚙️ Processes & System Control

- Process inspection
- Foreground / background jobs
- Signals
- Resource monitoring
- Service concepts
- Environment variables
- Exit status
- System troubleshooting

</td>
<td width="50%" valign="top">

### 💻 Shell & Automation

- Bash
- Pipes
- Redirection
- Command chaining
- Variables
- Conditions
- Loops
- Shell scripts

</td>
</tr>
</table>

> Individual exercises in this folder may focus on different subsets of these areas as the training evolves.

---

# 🖥️ Terminal Fundamentals

A Linux engineer spends less time memorizing commands and more time learning how to **combine small tools effectively**.

```bash
command input | process | filter | output
```

Example:

```bash
ps aux | grep application
```

or:

```bash
find . -name "*.cpp" | sort
```

The power of the Linux shell comes from composition:

```text
┌─────────┐    pipe     ┌─────────┐    pipe     ┌─────────┐
│ Command │ ──────────► │ Filter  │ ──────────► │ Output  │
└─────────┘             └─────────┘             └─────────┘
```

---

# 🧰 Essential Command Toolkit

| Category | Commands |
|---|---|
| **Navigation** | `pwd` `cd` `ls` |
| **Files** | `touch` `cp` `mv` `rm` `mkdir` |
| **Inspection** | `cat` `less` `head` `tail` `file` |
| **Search** | `find` `grep` `which` |
| **Permissions** | `chmod` `chown` `groups` |
| **Processes** | `ps` `top` `kill` `jobs` |
| **Storage** | `df` `du` `mount` |
| **Text Processing** | `grep` `sort` `uniq` `cut` `wc` |
| **Archives** | `tar` `gzip` |
| **Networking** | `ip` `ping` `ss` `curl` |
| **Development** | `gcc` `g++` `make` `cmake` `git` |

---

# 🔗 Pipes & Redirection

One of the most valuable Linux concepts is connecting commands together.

### Redirect output

```bash
command > output.txt
```

### Append output

```bash
command >> output.txt
```

### Redirect errors

```bash
command 2> error.log
```

### Pipe output to another command

```bash
cat file.txt | grep "error"
```

### Combine standard output and errors

```bash
command > build.log 2>&1
```

---

# 🔐 Linux Permissions

Linux permissions can be viewed as:

```text
        USER    GROUP   OTHER
        ───     ───     ───
        rwx     r-x     r--
```

Where:

| Permission | Meaning |
|---|---|
| `r` | Read |
| `w` | Write |
| `x` | Execute |

Example:

```bash
chmod 755 script.sh
```

Equivalent idea:

```text
Owner  → rwx
Group  → r-x
Other  → r-x
```

---

# ⚙️ Process Thinking

A useful troubleshooting flow:

```mermaid
flowchart LR
    A[Application] --> B[Process]
    B --> C[PID]
    C --> D[CPU / Memory]
    C --> E[Open Files]
    C --> F[Network]
    C --> G[Signals]
    G --> H[Stop / Restart / Debug]

    style A fill:#0D1117,color:#fff,stroke:#00FF88
    style B fill:#0D1117,color:#fff,stroke:#00FF88
    style C fill:#0D1117,color:#fff,stroke:#00C2FF
    style D fill:#0D1117,color:#fff,stroke:#7C3AED
    style E fill:#0D1117,color:#fff,stroke:#7C3AED
    style F fill:#0D1117,color:#fff,stroke:#7C3AED
    style G fill:#0D1117,color:#fff,stroke:#22C55E
    style H fill:#0D1117,color:#fff,stroke:#22C55E
```

Useful commands:

```bash
ps aux
top
pgrep application
kill <PID>
```

---

# 🧪 Bash Scripting

Bash turns repeated terminal actions into reusable workflows.

### Minimal example

```bash
#!/usr/bin/env bash

echo "Starting build..."

mkdir -p build
cd build || exit 1

cmake ..
cmake --build .

echo "Build completed."
```

Make it executable:

```bash
chmod +x build.sh
```

Run it:

```bash
./build.sh
```

---

# 🏗️ Linux Developer Workflow

```text
SOURCE CODE
    │
    ▼
┌──────────────┐
│   Editor     │
│ VS Code/Vim  │
└──────┬───────┘
       │
       ▼
┌──────────────┐
│ Build Tools  │
│ GCC / CMake  │
└──────┬───────┘
       │
       ▼
┌──────────────┐
│ Executable   │
└──────┬───────┘
       │
       ▼
┌──────────────┐
│ Linux Runtime│
└──────┬───────┘
       │
       ▼
┌──────────────┐
│ Debug / Logs │
└──────────────┘
```

---

# 🛠️ Development Stack

<p align="center">

<img src="https://img.shields.io/badge/Linux-Development-00FF88?style=for-the-badge&logo=linux&logoColor=white&labelColor=0D1117"/>
<img src="https://img.shields.io/badge/Bash-Scripting-4EAA25?style=for-the-badge&logo=gnubash&logoColor=white&labelColor=0D1117"/>
<img src="https://img.shields.io/badge/GNU-GCC-A42E2B?style=for-the-badge&logo=gnu&logoColor=white&labelColor=0D1117"/>
<img src="https://img.shields.io/badge/CMake-Build-064F8C?style=for-the-badge&logo=cmake&logoColor=white&labelColor=0D1117"/>
<img src="https://img.shields.io/badge/Git-Version%20Control-F05032?style=for-the-badge&logo=git&logoColor=white&labelColor=0D1117"/>

</p>

---

# 🚀 Getting Started

Clone the full ITI repository:

```bash
git clone https://github.com/mohamedabdelmajeed-eng/ITI.git
```

Enter the repository:

```bash
cd ITI
```

Open the Linux training folder:

```bash
cd Linux
```

List the available material:

```bash
ls -la
```

Inspect the current working directory:

```bash
pwd
```

---

# 🧠 Engineering Skills Developed

This Linux training journey strengthens my ability to:

- ✅ Work confidently from the command line
- ✅ Navigate and understand the Linux filesystem
- ✅ Manage files and directories efficiently
- ✅ Understand ownership and permissions
- ✅ Inspect and control running processes
- ✅ Combine shell utilities using pipes
- ✅ Redirect and analyze command output
- ✅ Automate repetitive work with Bash
- ✅ Use Linux as a C/C++ development environment
- ✅ Debug software through processes, logs, and system state
- ✅ Use Git from the terminal
- ✅ Prepare for embedded and automotive Linux workflows

---

# 🐧 Linux as an Engineering Platform

Linux connects multiple areas of this ITI learning journey.

```mermaid
flowchart LR
    A[C++ Development] --> D[Linux]
    B[Build Tools] --> D
    C[Git / Shell] --> D
    D --> E[Qt Applications]
    D --> F[Embedded Systems]
    D --> G[Automotive Software]
    E --> H[IVI Applications]
    F --> H
    G --> H

    style D fill:#10251B,color:#fff,stroke:#00FF88,stroke-width:3px
    style A fill:#0D1117,color:#fff,stroke:#00599C
    style B fill:#0D1117,color:#fff,stroke:#00C2FF
    style C fill:#0D1117,color:#fff,stroke:#F05032
    style E fill:#0D1117,color:#fff,stroke:#41CD52
    style F fill:#0D1117,color:#fff,stroke:#7C3AED
    style G fill:#0D1117,color:#fff,stroke:#00C2FF
    style H fill:#0D1117,color:#fff,stroke:#22C55E
```

---

# 🚘 From Linux to Automotive IVI

Within the complete repository, the progression is:

<div align="center">

### ⚙️ C++ Programming

⬇

### 🐧 Linux Environment

⬇

### 🖥️ Qt GUI Development

⬇

### 🔗 System Integration

⬇

# 🎧 Sonique IVI Audio Player

**USB • Bluetooth • Automotive Infotainment**

</div>

<p align="center">

<a href="../C%2B%2B">
  <img src="https://img.shields.io/badge/PREVIOUS-C%2B%2B%20Training-00599C?style=for-the-badge&logo=cplusplus&logoColor=white&labelColor=0D1117"/>
</a>

<a href="../QT">
  <img src="https://img.shields.io/badge/NEXT-Qt%20Development-41CD52?style=for-the-badge&logo=qt&logoColor=white&labelColor=0D1117"/>
</a>

</p>

<p align="center">
  <a href="../Grad_Project/Sonique_IVIAudioPlayer_USB_Bluetooth_Final">
    <img src="https://img.shields.io/badge/FEATURED-Sonique%20IVI%20Graduation%20Project-00C2FF?style=for-the-badge&labelColor=0D1117"/>
  </a>
</p>

---

# 🔍 Troubleshooting Mindset

When something fails on Linux, investigate systematically:

```text
1. COMMAND
     │
     ▼
2. EXIT STATUS
     │
     ▼
3. PERMISSIONS
     │
     ▼
4. PATH / ENVIRONMENT
     │
     ▼
5. PROCESS STATE
     │
     ▼
6. LOGS / ERROR OUTPUT
     │
     ▼
7. DEPENDENCIES
     │
     ▼
8. ROOT CAUSE
```

Examples:

```bash
echo $?
which g++
env
ps aux
df -h
free -h
```

---

# ✅ Linux Practice Checklist

Before considering a Linux exercise complete:

- [ ] I understand what each command does
- [ ] I can explain the path being used
- [ ] Permissions are intentional
- [ ] Destructive commands are used carefully
- [ ] Errors are inspected instead of ignored
- [ ] Repeated steps are candidates for scripting
- [ ] Scripts have meaningful names
- [ ] Exit codes are considered
- [ ] Commands are documented when non-obvious
- [ ] The workflow can be reproduced

---

# 🧩 Terminal Productivity Tips

### Command history

```bash
history
```

### Search history

```text
Ctrl + R
```

### Autocomplete

```text
TAB
```

### Stop a foreground process

```text
Ctrl + C
```

### Clear terminal

```bash
clear
```

### Read command documentation

```bash
man <command>
```

Example:

```bash
man grep
```

---

# 🔭 Future Improvements

As this Linux folder grows, useful enhancements include:

- [ ] Add an index of every Linux exercise
- [ ] Add a Bash scripting section
- [ ] Add command examples beside each lab
- [ ] Add sample terminal output
- [ ] Add filesystem diagrams
- [ ] Add permissions exercises
- [ ] Add process-management labs
- [ ] Add networking fundamentals
- [ ] Add shell automation projects
- [ ] Add systemd/service examples
- [ ] Add debugging tools
- [ ] Add Linux + C++ build workflows
- [ ] Add embedded Linux notes where applicable

---

# 📚 Recommended Documentation Style

For every larger Linux exercise or script:

```text
Exercise / Script
│
├── Objective
├── Concepts Used
├── Commands
├── Implementation
├── Example Output
├── Troubleshooting
└── Key Learnings
```

This turns isolated terminal work into a **clear engineering portfolio**.

---

# 🤝 Feedback & Collaboration

Constructive technical feedback is always welcome.

If you see an opportunity to improve the work:

1. Open an **Issue**
2. Suggest a cleaner approach
3. Fork the repository
4. Submit a Pull Request

---

## 👨‍💻 Maintainer

<div align="center">

### @mohamedabdelmajeed-eng

**C++ • Linux • Qt • Embedded • Automotive Software**

<a href="https://github.com/mohamedabdelmajeed-eng">
  <img src="https://img.shields.io/badge/GitHub-mohamedabdelmajeed--eng-181717?style=for-the-badge&logo=github&logoColor=white"/>
</a>

<br/><br/>

⭐ **If you find this learning journey useful, consider starring the main ITI repository.**

</div>

---

<div align="center">

### 🐧 Master the terminal. Understand the system. Engineer with confidence.

<img width="100%" src="https://capsule-render.vercel.app/api?type=waving&color=0:00FF88,50:10251B,100:0D1117&height=130&section=footer"/>

</div>
