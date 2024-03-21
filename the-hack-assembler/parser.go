package main

import (
	"fmt"
	"strconv"
	"strings"
)

func parseAsmLine(asmLine string) string {
	// trim any whitespace
	asmLine = strings.TrimSpace(asmLine)

	if strings.HasPrefix(asmLine, "@") {
		fmt.Println("A-instruction: ", asmLine)
		return parseAInstruction(asmLine)
	}
	fmt.Println("C-instruction: ", asmLine)
	return parseCInstruction(asmLine)
}

func parseAInstruction(line string) string {
	// remove the @
	line = strings.TrimPrefix(line, "@")
	// remove the R if it's a variable
	if line[0] == 'R' {
		line = line[1:]
	}
	// convert the number to binary
	address, err := strconv.Atoi(line)
	checkErr(err)
	binaryRep := strconv.FormatInt(int64(address), 2)
	// pad with 0s
	for len(binaryRep) < 16 {
		binaryRep = "0" + binaryRep
	}
	return binaryRep
}

func parseCInstruction(line string) string {
	// split the line into dest, comp, and jump
	dest, comp, jump := splitCInstructionParts(line)
	// convert each part to binary and combine them into one string + 111 for C-instruction
	binaryRep := "111" + compTable[comp] + destTable[dest] + jumpTable[jump]
	return binaryRep
}

func splitCInstructionParts(line string) (dest, comp, jump string) {
	// I assume that the dest part is optional
	if strings.Contains(line, "=") {
		parts := strings.Split(line, "=")
		dest = parts[0]
		line = parts[1]
	}
	if strings.Contains(line, ";") {
		parts := strings.Split(line, ";")
		comp = parts[0]
		jump = parts[1]
	} else {
		comp = line
	}
	return dest, comp, jump
}
