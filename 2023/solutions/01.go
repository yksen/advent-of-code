package solutions

import (
	"log"
	"strings"
)

func check(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

var digitLookup = map[string]int{
	"one":   1,
	"two":   2,
	"three": 3,
	"four":  4,
	"five":  5,
	"six":   6,
	"seven": 7,
	"eight": 8,
	"nine":  9,
}

func isDigit(char rune) bool {
	return char >= '0' && char <= '9'
}

type IndexDigit struct {
	Index int
	Digit int
}

func parseNumber(line string) int {
	leftmost, rightmost := IndexDigit{len(line), -1}, IndexDigit{-1, -1}
	for word, digit := range digitLookup {
		index := strings.Index(line, word)
		if index >= 0 && index < leftmost.Index {
			leftmost = IndexDigit{index, digit}
		}
		index = strings.LastIndex(line, word)
		if index > rightmost.Index {
			rightmost = IndexDigit{index, digit}
		}
	}

	for i := 0; i < len(line); i++ {
		if isDigit(rune(line[i])) && i < leftmost.Index {
			leftmost.Digit = int(line[i] - '0')
			break
		}
	}
	for i := len(line) - 1; i >= 0; i-- {
		if isDigit(rune(line[i])) && i > rightmost.Index {
			rightmost.Digit = int(line[i] - '0')
			break
		}
	}

	return leftmost.Digit*10 + rightmost.Digit
}

func Day01(input []string) int {
	total := 0
	for _, line := range input {
		total += parseNumber(line)
	}
	return total
}
