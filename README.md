# Call Stack Visualizer and Profiler

## Overview
The Call Stack Visualizer and Profiler is a tool to profile, monitor, and analyze stack frames during program execution. It provides functionality to record detailed stack frame metadata, aiding in debugging and performance profiling.

## Features
- **Instrumentation**:
  - Tracks function entry and exit points.
  - Captures start and end times for each function.
  - Records metadata such as frame pointers, caller information, process IDs, and memory ranges.

- **Visualization**:
  - Sorts and displays stack frame data based on:
    - Start time (`-s`)
    - Finish time (`-f`)
    - Process IDs (`-p`)
  - Displays function metadata, including stack frame boundaries and execution time.

- **Support for Multiple Scenarios**:
  - **`testfork`**: Simulates forked processes and tracks stack behavior in a multitasking environment.
  - **`testpipe`**: Demonstrates inter-process communication using non-blocking pipes.
  - **`stackviz`**: A visualizer for stack frame analysis and sorting.

