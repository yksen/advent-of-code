package solutions

import (
	"strconv"
	"strings"
)

func parseList(list string) []int {
	result := make([]int, 0)
	for _, numberStr := range strings.Split(list, " ") {
		numberStr = strings.TrimSpace(numberStr)
		if numberStr != "" {
			number, err := strconv.Atoi(numberStr)
			check(err)
			result = append(result, number)
		}
	}
	return result
}

func contains(list []int, number int) bool {
	for _, item := range list {
		if item == number {
			return true
		}
	}
	return false
}

func Day04(input []string) (int, int) {
	totalPoints := 0
	cardCount := 0
	cardCopies := make(map[int]int)
	for n, line := range input {
		lists := strings.Split(line[strings.Index(line, ":")+1:], "|")
		winningNumbers := parseList(lists[0])
		numbers := parseList(lists[1])
		points := 0
		copies := 0
		for _, number := range numbers {
			if contains(winningNumbers, number) {
				if points == 0 {
					points = 1
				} else {
					points *= 2
				}
				copies++
			}
		}
		totalPoints += points
		cardCopies[n] += 1
		for copies > 0 {
			cardCopies[n+copies] += cardCopies[n]
			copies--
		}
	}

	for _, copies := range cardCopies {
		cardCount += copies
	}
	return totalPoints, cardCount
}
