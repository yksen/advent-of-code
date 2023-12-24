package solutions

import "fmt"

type stringPair struct {
	first  string
	second string
}

func allEndWithChar(nodes []string, char byte) bool {
	for _, node := range nodes {
		if node[len(node)-1] != char {
			return false
		}
	}
	return true
}

func Day08(input []string) (int, int) {
	instructions := input[0]

	directionsMap := make(map[string]stringPair)
	for i := 2; i < len(input); i++ {
		var current string
		var left string
		var right string
		fmt.Sscanf(input[i], "%3s = (%3s, %3s)", &current, &left, &right)
		directionsMap[current] = stringPair{left, right}
	}

	currentNode := "AAA"
	instructionIndex := 0
	steps := 0
	for currentNode != "ZZZ" {
		steps++
		instruction := instructions[instructionIndex]
		instructionIndex = (instructionIndex + 1) % len(instructions)
		if instruction == 'L' {
			currentNode = directionsMap[currentNode].first
		} else {
			currentNode = directionsMap[currentNode].second
		}
	}

	instructionIndex = 0
	steps2 := 0
	nodes := make([]string, 0)
	for i := 2; i < len(input); i++ {
		if input[i][2] == 'A' {
			nodes = append(nodes, input[i][:3])
		}
	}
	for !allEndWithChar(nodes, 'Z') {
		steps2++
		instruction := instructions[instructionIndex]
		instructionIndex = (instructionIndex + 1) % len(instructions)
		for _, node := range nodes {
			if instruction == 'L' {
				nodes = append(nodes, directionsMap[node].first)
			} else {
				nodes = append(nodes, directionsMap[node].second)
			}
		}
	}
	return steps, steps2
}
