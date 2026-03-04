# Parallel File Encryptor (C++)

A process-parallel C++ utility that recursively scans directories and encrypts or decrypts files using a streaming XOR cipher. The program demonstrates systems programming concepts such as process creation with `fork()`, filesystem traversal, task distribution, and environment-based secret management.

---

## Features

- Recursive directory traversal using `std::filesystem`
- Process-level parallelism using `fork()`
- Streaming file encryption (handles large files without loading entire files into memory)
- Environment-based encryption key management
- Task-based workload partitioning across worker processes
- Modular C++ design
- CMake-based build system

---

## Project Structure

```
file-encryptor/
│
├── CMakeLists.txt
├── main.cpp
├── FileDiscoverer.cpp
├── FileDiscoverer.h
├── Task.h
├── TaskQueue.cpp
├── TaskQueue.h
├── Worker.cpp
├── Worker.h
├── CryptoEngine.cpp
├── CryptoEngine.h
└── build/
```

---

## Components

### main.cpp
Entry point of the program.

Responsibilities:
- Parses command line arguments
- Initializes directory scanning
- Launches the task queue and worker processes

---

### FileDiscoverer

Responsible for directory traversal.

Functions:
- Recursively scans directories
- Identifies regular files
- Generates encryption/decryption tasks

Uses:

```cpp
std::filesystem::recursive_directory_iterator
```

---

### Task

Defines a unit of work.

Each task contains:

```
TaskType (Encrypt / Decrypt)
File path
```

Tasks allow file operations to be processed independently.

---

### TaskQueue

Responsible for distributing tasks across worker processes.

Responsibilities:
- Manages task lists
- Spawns worker processes using `fork()`
- Waits for workers to complete execution

---

### Worker

Executes assigned tasks.

Responsibilities:
- Processes files assigned to the worker
- Calls the encryption engine
- Handles errors for individual files

Workers run independently, allowing parallel processing.

---

### CryptoEngine

Handles encryption and decryption.

Responsibilities:
- Loads encryption key from environment variable
- Streams file data in chunks
- Applies XOR-based encryption

Core function:

```cpp
transform(input_file, output_file)
```

This ensures large files can be processed without loading the entire file into memory.

---

## Build Instructions

### Requirements

- C++17 compatible compiler
- CMake
- Unix-like environment (Linux or macOS)

Example installation on macOS:

```bash
brew install cmake
```

---

### Build the Project

From the project root directory:

```bash
mkdir build
cd build
cmake ..
make
```

This produces the executable:

```
encryptor
```

---

## Usage

The program requires an encryption key provided via an environment variable.

### Set Encryption Key

```bash
export ENCRYPTION_KEY=mysecretkey
```

---

### Encrypt Files

```bash
./encryptor encrypt ../testdir 4
```

---

### Decrypt Files

```bash
./encryptor decrypt ../testdir 4
```

---

### Command Format

```
./encryptor <encrypt|decrypt> <directory> <num_workers>
```

Example:

```bash
./encryptor encrypt ../testdir 4
```

Meaning:

- `encrypt` → encryption mode
- `../testdir` → directory containing files
- `4` → number of worker processes

---

## Example Workflow

Create a directory with test files:

```bash
mkdir testdir
echo "hello world" > testdir/file1.txt
echo "example file" > testdir/file2.txt
```

Run encryption:

```bash
./encryptor encrypt ../testdir 4
```

Directory contents after encryption:

```
file1.txt
file1.txt.enc
file2.txt
file2.txt.enc
```

Run decryption:

```bash
./encryptor decrypt ../testdir 4
```

Output files:

```
file1.txt.enc.dec
file2.txt.enc.dec
```

---

## Verifying Correctness

To confirm encryption and decryption work properly:

```bash
diff ../testdir/file1.txt ../testdir/file1.txt.enc.dec
```

If nothing prints, the files are identical.

You can also compare hashes:

```bash
shasum ../testdir/file1.txt
shasum ../testdir/file1.txt.enc.dec
```

Matching hashes confirm the decrypted file matches the original.

---

## Encryption Design

This project uses a simple XOR cipher.

Encryption logic:

```
encrypted_byte = file_byte XOR key_byte
```

Decryption applies the same operation:

```
original_byte = encrypted_byte XOR key_byte
```

Because XOR is reversible:

```
A XOR B XOR B = A
```

The key repeats across the file and encryption is applied in streaming chunks.

⚠️ Note: XOR encryption is used for demonstration purposes only and is not cryptographically secure.

---

## Parallel Processing

The program uses process-based parallelism.

Worker processes are created using:

```cpp
fork()
```

Tasks are distributed deterministically across workers.

Example:

```
worker_0 → tasks[0], tasks[4], tasks[8]
worker_1 → tasks[1], tasks[5], tasks[9]
worker_2 → tasks[2], tasks[6], tasks[10]
worker_3 → tasks[3], tasks[7], tasks[11]
```

This avoids synchronization overhead while enabling efficient parallel processing.

---

## Debugging

Compile with debug symbols:

```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

Run with a debugger:

```bash
lldb ./encryptor
```

Set breakpoints:

```
breakpoint set --name CryptoEngine::transform
```

Then run:

```
run encrypt ../testdir 4
```

---

## Testing Suggestions

### Many files

```bash
for i in {1..50}; do
echo "test $i" > ../testdir/file$i.txt
done
```

---

### Binary files

```bash
dd if=/dev/urandom of=../testdir/random.bin bs=1M count=5
```

---

### Large files

```bash
dd if=/dev/urandom of=../testdir/bigfile.bin bs=1M count=100
```

These tests verify streaming and parallel processing behavior.

---

## Concepts Demonstrated

This project demonstrates:

- Process-based parallelism
- Filesystem traversal using `std::filesystem`
- Streaming file processing
- Task-based workload distribution
- Environment-based secret management
- Modular C++ system design
- CMake build systems

---

## Future Improvements

Possible extensions:

- Replace XOR with AES encryption using OpenSSL
- Implement dynamic task queues with IPC
- Add file integrity verification
- Add structured logging
- Introduce automated unit tests

---

## License

MIT License
