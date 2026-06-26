# MIPS Processor Architecture Simulator

A modular, cycle-accurate single-cycle MIPS CPU simulator written in C++. This project models the complete physical 5-stage instruction pipeline (**Fetch, Decode, Execute, Memory, and Write-back**) using object-oriented architectural components. 

---

## System Architecture & Features

The simulator mirrors physical hardware structures down to the exact wire behaviors:
*   **5-Stage Instruction Pipeline:** Explicit methods partition execution into discrete hardware phases (`IF()`, `ID()`, `EX()`, `MEM()`, `WB()`).
*   **Combinatorial Control & ALU Control Units:** Evaluates instruction opcodes and `funct` fields dynamically to assert accurate internal control signals (e.g., `RegDst`, `ALUSrc`, `MemToReg`).
*   **Multi-Ported Register File:** Simulates independent parallel dual-channel reads (`RD1` and `RD2`) along with hardwired `$zero` register write protections.
*   **Byte-Addressable Data Memory:** Models word alignment requirements, enforcing strict 4-byte boundaries and throwing hardware-like exceptions on unaligned accesses.
*   **Bit-Accurate Branch/Jump Addressing:** Computes accurate relative branch offsets using left-shifts (`<< 2`) and resolves jump targets via upper Program Counter (PC) masking.

---

## Supported Instruction Set Architecture (ISA)

The custom assembler parses raw assembly lines into internal machine representations supporting:
*   **R-Type:** `add`, `sub`
*   **I-Type:** `addi`, `lw`, `sw`, `beq`
*   **J-Type:** `j`
*   **Control:** `halt`

---

## File Structure

```text
MIPS Simulator/
├── .gitignore
├── README.md
├── main.cpp                  # Main application entry point
│
├── Assembler/                # Contains your custom text-parsing tools
│   ├── instructions.h
│   ├── registers.h
│   └── assembler.cpp
│
└── Processor/                # Contains all your virtual CPU circuitry components
    ├── alu.cpp
    ├── control_unit.cpp
    ├── register_file.cpp
    ├── data_memory.cpp
    ├── instruction_memory.cpp
    └── processor.cpp
