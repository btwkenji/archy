## Archy - zip archive compressor/extraction using c++

###

<div align="center">
  <img src="https://cdn.jsdelivr.net/gh/devicons/devicon/icons/cplusplus/cplusplus-original.svg" height="150" alt="cplusplus logo"  />
</div>

###

## Project structure:

```rust
archy
│
├── LICENSE
├── archy.cpp
└── README.md
```

## Installation

```sh
git clone https://github.com/kenjitheman/archy
```

## Usage

- **Modify main function to use this tool**

```c++
std::vector<std::string> filesToCompress = {"your_file_path.txt", "your_file_path_1.txt"}; // can be any number of files
std::string zipFilename = "your_zip_archive.zip";
```

- Compile c++

```sh
g++ archy.cpp -o archy
```

- Run:

```sh
./archy
```

## Contributing

- Pull requests are welcome, for major changes, please open an issue first to
  discuss what you would like to change.

## license

- [MIT](https://choosealicense.com/licenses/mit/)
