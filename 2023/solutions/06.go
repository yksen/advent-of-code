package solutions

import (
	"strconv"
	"strings"
)

func getWays(record, distance int) int {
	ways := 0
	for j := 1; j < record; j++ {
		if j*(record-j) > distance {
			ways++
		}
	}
	return ways
}

func Day06(input []string) (int, int) {
	product := 1
	records := parseNumbers(input[0][strings.Index(input[0], ":")+1:])
	distances := parseNumbers(input[1][strings.Index(input[1], ":")+1:])

	for i := 0; i < len(records); i++ {
		product *= getWays(records[i], distances[i])
	}

	recordStr := ""
	distanceStr := ""
	for i := 0; i < len(records); i++ {
		recordStr += strconv.Itoa(records[i])
		distanceStr += strconv.Itoa(distances[i])
	}
	record, err := strconv.Atoi(recordStr)
	check(err)
	distance, err := strconv.Atoi(distanceStr)
	check(err)

	return product, getWays(record, distance)
}
