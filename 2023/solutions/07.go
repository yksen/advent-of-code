package solutions

import (
	"slices"
	"strconv"
	"strings"
)

var cardValue = map[rune]int{
	'2': 2,
	'3': 3,
	'4': 4,
	'5': 5,
	'6': 6,
	'7': 7,
	'8': 8,
	'9': 9,
	'T': 10,
	'J': 11,
	'Q': 12,
	'K': 13,
	'A': 14,
}

func getHighestCount(m map[rune]int) (rune, int) {
	maxKey, max := rune(' '), 0
	for k, v := range m {
		if v > max {
			max = v
			maxKey = k
		}
	}
	return maxKey, max
}

func getSecondHighestCount(m map[rune]int) (rune, int) {
	maxKey, max := rune(' '), 0
	for k, v := range m {
		if v > max && k != 'J' {
			max = v
			maxKey = k
		}
	}
	return maxKey, max
}

type hand struct {
	cards string
	bid   int
}

func cardsCompare(a, b string, cv map[rune]int) int {
	for i := 0; i < len(a); i++ {
		if a[i] != b[i] {
			return cv[rune(a[i])] - cv[rune(b[i])]
		}
	}
	return 0
}

func getCardCounts(cards string) map[rune]int {
	m := map[rune]int{}
	for _, c := range cards {
		m[c]++
	}
	return m
}

func handCompare(a, b hand) int {
	am, bm := getCardCounts(a.cards), getCardCounts(b.cards)
	al, bl := len(am), len(bm)
	_, ah := getHighestCount(am)
	_, bh := getHighestCount(bm)

	if al == bl {
		if ah != bh {
			return ah - bh
		}
		return cardsCompare(a.cards, b.cards, cardValue)
	}

	return bl - al
}

func handCompareJokers(a, b hand) int {
	cardValueJoker := map[rune]int{}
	for k, v := range cardValue {
		cardValueJoker[k] = v
	}
	cardValueJoker['J'] = 1

	am, bm := getCardCounts(a.cards), getCardCounts(b.cards)
	al, bl := len(am), len(bm)
	ahr, ah := getHighestCount(am)
	bhr, bh := getHighestCount(bm)
	aj, bj := am['J'], bm['J']
	if ahr == 'J' {
		_, aj = getSecondHighestCount(am)
	}
	if bhr == 'J' {
		_, bj = getSecondHighestCount(bm)
	}

	nal, nbl := clamp(al-clamp(aj, 0, 1), 1, 5), clamp(bl-clamp(bj, 0, 1), 1, 5)
	nah, nbh := clamp(ah+aj, 1, 5), clamp(bh+bj, 1, 5)

	if nal == nbl {
		if nah != nbh {
			return nah - nbh
		}
		return cardsCompare(a.cards, b.cards, cardValueJoker)
	}

	return nbl - nal
}

func Day07(input []string) (int, int) {
	hands := make([]hand, 0)
	for _, line := range input {
		words := strings.Split(line, " ")
		bid, err := strconv.Atoi(words[1])
		check(err)
		hands = append(hands, hand{words[0], bid})
	}

	slices.SortFunc(hands, handCompare)
	sum := 0
	for i, hand := range hands {
		sum += (i + 1) * hand.bid
	}

	slices.SortFunc(hands, handCompareJokers)
	total := 0
	for i, hand := range hands {
		total += (i + 1) * hand.bid
	}

	return sum, total
}
