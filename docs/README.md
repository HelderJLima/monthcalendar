# monthcalendar

&#x20;

## 📌 About the Project

`monthcalendar` is a simple command-line application written in C that allows users to view a monthly calendar for any given year and month. The program also provides an option to save the generated calendar as a `.txt` file.

## 🛠 Features

- Allows the user to input a year and a month (Gregorian calendar)
- Displays a formatted monthly calendar in the terminal
- Provides an option to save the calendar to a text file
- Allows multiple queries without restarting

## 🚀 Installation & Usage

### Prerequisites

Make sure you have a C compiler installed on your system (e.g., GCC).

### Clone the Repository

```sh
git clone https://github.com/yourusername/monthcalendar.git
cd monthcalendar
```

### Compilation

```sh
gcc -o monthcalendar monthcalendar.c mcfunctions.c
```

### Running the Program

```sh
./monthcalendar
```

### Example Usage

1. The program asks for a **year** and **month**.
2. It displays the formatted monthly calendar in the terminal.
3. The user is prompted whether they want to save it as a `.txt` file.
4. If saved, the file path is displayed.
5. The program resets to allow another input or exit.

## 📂 Project Structure

The repository is organized as follows:

```plaintext
monthcalendar/
│── monthcalendar.c      # Main program file
│── mcfunctions.c        # Function implementations
│── mcfunctions.h        # Function headers
│── docs/               # Documentation and images
│   ├── README.md       # This README file
│   ├── screenshots/    # Images
│── output/             # Directory for saved calendar files
│── .gitignore          # Ignore compiled files
│── LICENSE             # Project license
```

## 🖼️ Example Images

Below are some screenshots demonstrating the program in action:

![Example 1](docs/screenshots/monthcalendar_example_01.png)
![Example 2](docs/screenshots/monthcalendar_example_02.png)
![Example 3](docs/screenshots/monthcalendar_example_03.png)
![Example 4](docs/screenshots/monthcalendar_example_04.png)



## 🤝 Contribution

Contributions are welcome! Feel free to open an issue or submit a pull request.

## 📜 License

This project is licensed under the GNU General Public License v3.0 (GPL-3.0). See the [LICENSE](LICENSE) file for details.

## 📞 Contact

- GitHub: [HelderJLima](https://github.com/HelderJLima)
- Email: [helder.lima.w@gmail.com](mailto:helder.lima.w@gmail.com)

