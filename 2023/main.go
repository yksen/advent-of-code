package main

import (
	"bufio"
	"fmt"
	"log"
	"os"

	"github.com/yksen/advent-of-code/2023/solutions"
)

func check(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

func main() {
	file, err := os.Open("input/08")
	check(err)
	defer file.Close()

	scanner := bufio.NewScanner(file)
	var lines []string
	for scanner.Scan() {
		lines = append(lines, scanner.Text())
	}

	fmt.Println(solutions.Day08(lines))
}
