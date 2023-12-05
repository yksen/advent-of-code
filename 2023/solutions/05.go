package solutions

import (
	"slices"
	"strconv"
	"strings"
)

func parseNumbers(input string) []int {
	numbersStr := strings.Split(input, " ")
	numbers := make([]int, 0)
	for _, numberStr := range numbersStr {
		if numberStr == "" {
			continue
		}
		number, err := strconv.Atoi(strings.TrimSpace(numberStr))
		check(err)
		numbers = append(numbers, number)
	}
	return numbers
}

type span struct {
	start int
	end   int
}

func updateValues(values []int, currentMap map[span]span) []int {
	for i, value := range values {
		for key, val := range currentMap {
			if value >= key.start && value < key.end {
				values[i] = val.start + (value - key.start)
			}
		}
	}
	return values
}

func Day05(input []string) (int, int) {
	values := parseNumbers(input[0][strings.Index(input[0], ":")+1:])
	currentMap := make(map[span]span)
	for _, line := range input[1:] {
		if strings.Contains(line, "map") {
			currentMap = make(map[span]span)
		} else if line != "" {
			numbers := parseNumbers(line)
			currentMap[span{numbers[1], numbers[1] + numbers[2]}] = span{numbers[0], numbers[0] + numbers[2]}
		} else {
			updateValues(values, currentMap)
		}
	}
	updateValues(values, currentMap)

	location := slices.Min(values)
	return location, 0
}
