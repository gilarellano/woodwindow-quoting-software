# Wood Window Quoting Software

This software is designed to automate the quoting process for a wood window manufacturing and installation company. It reads input specifications from a CSV file, calculates the quote using various parameters, and outputs the final quote and a detailed breakdown into separate CSV files.

## Directory Structure
```
├── src
│   ├── IOWindowQuotes.cpp
│   └── WoodWindow.cpp
├── include
│   ├── IOWindowQuotes.h
│   ├── WoodWindow.h
│   └── WindowConstants.h
├── bin
│   └── WoodWindow.exe
├── input
│   └── WindowSpecs.csv
├── output
│   ├── Window Quote.csv
│   └── Window Quote Breakdown.csv
├── test
├── Archive
└── README.md
```
- `src` directory: This directory contains the primary source code for our wood window quoting software. It contains the `IOWindowQuotes.cpp` and `WoodWindow.cpp` files which perform the main operations of reading the input data, calculating the quote, and generating output. Organizing our source files in a dedicated directory helps in quickly locating and managing the application's code.

- `include` directory: This directory holds the header files that provide the definitions and dependencies for our source code. This includes `IOWindowQuotes.h`, `WoodWindow.h`, and `WindowConstants.h`. The latter contains the pricing information used in the calculation of quotes. Keeping these files separate helps in easily locating and modifying these definitions, especially when pricing or other constants change.

- `bin` directory: This directory holds the compiled executable of our software, `WoodWindow.exe`. Keeping this separate from the source code allows us to easily find the executable that our clients will use to run the software.

- `input` directory: This directory is designed to hold the input data for our software. In this case, it's a `.csv` file named `WindowSpecs.csv`, which contains window specifications like measurements, quantity, type of glass, number of true divided lites, installation cost, and type of wood. Keeping this file separate makes it easier for us or our clients to update or replace the data without interfering with the rest of the project.

- `output` directory: This directory contains the output generated by our software, in the form of two .csv files - `Window Quote.csv` and `Window Quote Breakdown.csv`. The former is a simple representation of the pricing, while the latter provides a more detailed breakdown. Keeping these files in a separate directory simplifies the process of locating and sending these quotes to our clients.

- `test` directory: This directory is reserved for test code and data. It allows us to validate the functionality of our software, separate from the main application code. This separation ensures our main code remains clean and uncluttered, while also clearly delineating where our testing resources are.

## Getting Started

To get started with this project, clone the repository to your local machine.

```bash
https://github.com/gilarellano/woodwindow-quoting-software.git
```
Then, compile the C++ files:
```C++
g++ -o bin/WoodWindow src/*.cpp
```
To run the software, navigate to the bin directory and execute the following command:
```bash
./WoodWindow
```

## Running Tests
Navigate to the test directory and follow the instructions in the README.md file found there.

## Contributing
We welcome contributions to this project! Here's how you can contribute:

1. Fork the project.
2. Create your feature branch (git checkout -b feature/AmazingFeature).
3. Commit your changes (git commit -m 'Add some AmazingFeature').
4. Push to the branch (git push origin feature/AmazingFeature).
5. Open a Pull Request.
Please make sure your contributions adhere to our coding standards.

## Pull Request Process
Ensure any install or build dependencies are removed before the end of the layer when doing a build.
Update the README.md with details of changes to the interface, this includes new environment variables, exposed ports, useful file locations and container parameters.
You may merge the Pull Request once you have the sign-off of from the author.