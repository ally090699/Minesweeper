# Minesweeper Game

A simple implementation of the classic Minesweeper game built with Qt.

## Prerequisites

To build this project on macOS, you need to have the following tools installed:

- **Qt**
- **Xcode** (on macOS)

Follow these steps to compile and run the Minesweeper game:

1. **Login to SSH Server with GUI**:
```bash
ssh -X username@cs3307.gaul.csd.uwo.ca
```
2. **Configure the project with qmake**: 
```bash
qmake6
```
3. **Build the project**:
```bash
make
```
4. **Run the application**:
```bash
./Minesweeper
```

## Project Folder Setup

The project is organized as follows from the root project folder:

- **Minesweeper.pro**

- **Headers/**
  - `customButton.h`
  - `mainwindow.h`

- **Sources/**
  - `customButton.cpp`
  - `main.cpp`
  - `mainwindow.cpp`

- **Resources/**
  - `resources.qrc`
    - `:/icons`: prefix
      - `icons/`: folder containing all icon images used (e.g., `0.svg.png`).
