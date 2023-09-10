# Text Editor

## Table of Contents

1. [Introduction](#introduction)
2. [Features](#features)
3. [Technologies](#technologies)
4. [Getting Started](#getting-started)
   - [Prerequisites](#prerequisites)
   - [Installation](#installation)
   - [Usage](#usage)
5. [Architecture](#architecture)
6. [Contributing](#contributing)
7. [License](#license)
8. [Contact](#contact)
9. [Acknowledgements](#acknowledgements)

---

## Introduction

Text Editor is a simple yet feature-rich text editing application built using C++ and the Qt framework. This project aims to provide an easy-to-use interface for editing text files, complete with features like syntax highlighting, file management, and more.

---

## Features

- Multiple tabs for editing different files
- Syntax highlighting
- File management options like open, save, and delete
- [Add more features...]

---

## Technologies

- C++
- Qt Framework
- Doxygen (for code documentation)

---
## Documentation

La documentation du code est générée avec Doxygen. Voici comment générer et consulter la documentation.

### Installation de Doxygen

Si vous utilisez Ubuntu, vous pouvez installer Doxygen en utilisant la commande suivante :

\`\`\`bash
sudo apt-get install doxygen
\`\`\`

### Générer la Documentation

1. Placez-vous à la racine du projet où se trouve le fichier `Doxyfile`.
2. Exécutez la commande suivante :

\`\`\`bash
doxygen Doxyfile
\`\`\`

Cela générera la documentation dans le répertoire que vous aurez spécifié dans le champ `OUTPUT_DIRECTORY` de votre fichier `Doxyfile`.

### Lire la Documentation

#### Documentation HTML

1. Accédez au répertoire contenant la documentation (généralement un sous-dossier nommé `html`).
2. Ouvrez le fichier `index.html` avec votre navigateur web.

#### Documentation LaTeX

1. Accédez au répertoire contenant la documentation LaTeX (généralement un sous-dossier nommé `latex`).
2. Utilisez un éditeur LaTeX pour compiler les fichiers en PDF ou exécutez `pdflatex` en ligne de commande.

### Utilisation de Doxywizard

Si vous préférez utiliser une interface graphique :

1. Ouvrez Doxywizard.
2. Utilisez l'option "Fichier > Ouvrir..." pour ouvrir un fichier `Doxyfile` existant.
3. Cliquez sur "Run doxygen" pour générer la documentation.

## Getting Started

### Prerequisites

- C++ Compiler
- Qt Development Environment
- [Any other prerequisites...]

### Installation

1. Clone the repository
    ```bash
    git clone https://github.com/dicesare/textEditor.git
    ```
2. Open the project in Qt Creator and build it
3. [Other steps...]

### Usage

- Open the application
- A new, empty tab will open automatically, ready for text entry.
- Use `File -> Open` to open an existing file. This will open the file in a new tab.
- To save the contents of the active tab to a file, use `File -> Save` or `File -> Save As`.
---

## Architecture

Refer to the `docs/` folder for complete architecture and code documentation generated using Doxygen.

### Project Structure

- `src/`: Contains all the source code
  - `view/`: UI components
  - `controller/`: Business logic
  - `filemanagement/`: File I/O operations
- `docs/`: Contains Doxygen generated documentation
  - `html/`
  - `latex/`
- `.github/workflows`: GitHub Actions CI/CD scripts
- [Other folders...]

---

## Contributing

Contributions are always welcome! See `CONTRIBUTING.md` for ways to get started. Please adhere to this project's `CODE_OF_CONDUCT.md`.

---

## License

This project is licensed under the MIT License - see the `LICENSE` file for details.

---

## Contact

- Antony COCO - [LinkedIn](https://www.linkedin.com/in/antonycoco/)
- Email - antony.coco.pro@gmail.com

---

