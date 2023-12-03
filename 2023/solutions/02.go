package solutions

import (
	"strconv"
	"strings"
)

var cubeCount = map[string]int{
	"red":   12,
	"green": 13,
	"blue":  14,
}

func getId(str string) int {
	id := strings.Split(str, " ")[1]
	id = id[:len(id)-1]
	val, err := strconv.Atoi(id)
	check(err)
	return val
}

func isPossible(str string) bool {
	sets := strings.Split(str, ";")
	for _, set := range sets {
		cubes := strings.Split(set, ",")
		for _, cube := range cubes {
			details := strings.Split(cube, " ")
			val, err := strconv.Atoi(details[1])
			check(err)
			color := details[2]
			if val > cubeCount[color] {
				return false
			}
		}
	}
	return true
}

func getPower(str string) int {
	mins := map[string]int{
		"red":   0,
		"green": 0,
		"blue":  0,
	}
	sets := strings.Split(str, ";")
	for _, set := range sets {
		cubes := strings.Split(set, ",")
		for _, cube := range cubes {
			details := strings.Split(cube, " ")
			val, err := strconv.Atoi(details[1])
			check(err)
			color := details[2]
			if mins[color] < val {
				mins[color] = val
			}
		}
	}

	product := 1
	for _, value := range mins {
		product *= value
	}
	return product
}

func Day02(input []string) (int, int) {
	total, power := 0, 0
	for _, line := range input {
		game := line[strings.Index(line, ":")+1:]
		if isPossible(game) {
			total += getId(line)
		}
		power += getPower(game)
	}
	return total, power
}
