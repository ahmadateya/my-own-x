package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func checkErr(e error) {
	if e != nil {
		panic(e)
	}
}

func main() {
	// take the file name from the command line
	asmFileName := os.Args[1]
	// open the file
	asmFile, err := os.Open(asmFileName)
	checkErr(err)
	defer asmFile.Close()

	hackRep := assemble(asmFile)
	fmt.Println(hackRep)

	// remove the .asm extension
	fileName := strings.TrimSuffix(asmFileName, ".asm")
	// write the binary to a new file
	hackFile, err := os.Create(fileName + ".hack")
	checkErr(err)
	_, err = hackFile.WriteString(hackRep)
	checkErr(err)
	defer hackFile.Close()
}

func assemble(asmFile *os.File) string {
	hackRep := ""

	// read line by line; for each line, parse it and add the binary representation to hackRep
	fileScanner := bufio.NewScanner(asmFile)
	for fileScanner.Scan() {
		asmLine := fileScanner.Text()
		if strings.HasPrefix(asmLine, "//") || len(asmLine) == 0 {
			continue
		}
		hackLine := parseAsmLine(asmLine)

		hackRep = hackRep + hackLine + "\n"
	}
	return hackRep
}
