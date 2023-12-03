package solutions

import (
	"strconv"
	"strings"
	"unicode"
)

func clamp(value int, min int, max int) int {
	if value < min {
		return min
	}
	if value > max {
		return max
	}
	return value
}

func getAdjacencySubstring(input []string, n int, left int, right int) string {
	left = clamp(left-1, 0, len(input[n])-1)
	right = clamp(right+1, 0, len(input[n])-1)

	substring := input[n][left:right]
	if n > 0 {
		substring += input[n-1][left:right]
	}
	if n < len(input)-1 {
		substring += input[n+1][left:right]
	}
	return substring
}

func readNumbers(line string, l int, r int) []int {
	numbers := make([]int, 0)
	for i := l; i <= r; i++ {
		if unicode.IsDigit(rune(line[i])) {
			left, right := i, i
			for left >= 0 && unicode.IsDigit(rune(line[left])) {
				left--
			}
			for right < len(line) && unicode.IsDigit(rune(line[right])) {
				right++
			}
			left, right = clamp(left+1, 0, len(line)-1), clamp(right, 0, len(line))
			number, err := strconv.Atoi(line[left:right])
			check(err)
			numbers = append(numbers, number)
			i = right
		}
	}
	return numbers
}

func Day03(input []string) (int, int) {
	sum := 0
	for n, line := range input {

		for i := 0; i < len(line); i++ {
			left, right := i, i
			if unicode.IsDigit(rune(line[i])) {
				for i < len(line) && unicode.IsDigit(rune(line[i])) {
					i++
				}
				right = i
				number, err := strconv.Atoi(line[left:right])
				check(err)

				substring := getAdjacencySubstring(input, n, left, right)
				if strings.ContainsFunc(substring, func(r rune) bool {
					return r != '.' && !unicode.IsDigit(r)
				}) {
					sum += number
				}
			}
		}
	}

	debug := 0
	total := 0
	for n, line := range input {
		i := 0
		for strings.Contains(line[i:], "*") {
			numbers := make([]int, 0)
			i += strings.Index(line[i:], "*")
			left, right := clamp(i-1, 0, len(line)-1), clamp(i+1, 0, len(line)-1)
			if n > 0 {
				numbers = append(numbers, readNumbers(input[n-1], left, right)...)
			}
			numbers = append(numbers, readNumbers(line, left, right)...)
			if n < len(input)-1 {
				numbers = append(numbers, readNumbers(input[n+1], left, right)...)
			}
			if len(numbers) == 2 {
				total += numbers[0] * numbers[1]
				debug++
			}
			i++
		}
	}
	return sum, total
}
