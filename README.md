# get_next_line

`get_next_line` is a function that aims to implement a function capable of reading the next line from a file descriptor.

---

## Overview

`get_next_line` is a simple yet efficient function for reading files line by line. It can handle large text files and binary files seamlessly.

### Project Features:
- Supports reading files with very long lines.
- Utilizes dynamic memory allocation to manage data.
- Written in **C** and adheres to 42 School standards.

---

## Installation

1. Clone the repository to your local machine:
   ```bash
   git clone https://github.com/username/get_next_line.git
   cd get_next_line
   ```

2. Add `get_next_line.c` and `get_next_line.h` to your project.

---

## Usage

1. Create an executable that integrates the `get_next_line` function, for example:

  ```c
  #include "get_next_line.h"
  #include <fcntl.h>
  #include <stdio.h>

  int main(void)
  {
    int  fd = open("test.txt", O_RDONLY);
    char  *line;

    if (fd < 0)
        return (1);

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
  }
   ```

   2. Compile the code using:
      ```bash
       gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c -o get_next_line
       ```

   4. Run the executable:
      ```bash
      ./get_next_line
      ```

---

## Performance

- **BUFFER_SIZE**: You can adjust the buffer size (BUFFER_SIZE) to optimize performance based on the type of files you're handling.


















   
