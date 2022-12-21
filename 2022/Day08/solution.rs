use std::{
    fs::File,
    io::{BufRead, BufReader},
};

fn main() {
    let file_path = "input.txt";
    let input = get_input(file_path);

    println!("{}", part_one(&input));
    println!("{}", part_two(&input));
}

fn get_input(file_path: &str) -> Vec<Vec<u8>> {
    let file = File::open(file_path).unwrap();
    let reader = BufReader::new(file);
    reader
        .lines()
        .map(|line| {
            line.unwrap()
                .chars()
                .map(|c| c.to_digit(10).unwrap() as u8)
                .collect()
        })
        .collect()
}

fn part_one(map: &Vec<Vec<u8>>) -> usize {
    let mut visible_trees = 0;
    for x in 0..map.len() {
        for y in 0..map.len() {
            let mut visible_sides = 4;

            if map[..x].iter().any(|row| row[y] >= map[x][y]) {
                visible_sides -= 1;
            }

            if map[x + 1..].iter().any(|row| row[y] >= map[x][y]) {
                visible_sides -= 1;
            }

            if map[x].iter().take(y).any(|&v| v >= map[x][y]) {
                visible_sides -= 1;
            }

            if map[x].iter().skip(y + 1).any(|&v| v >= map[x][y]) {
                visible_sides -= 1;
            }

            if visible_sides > 0 {
                visible_trees += 1;
            }
        }
    }
    visible_trees
}

fn part_two(map: &Vec<Vec<u8>>) -> usize {
    let mut highest_scenic_score = 1;

    for y in 0..map.len() {
        for x in 0..map.len() {
            let mut up = 0;
            let mut down = 0;
            let mut left = 0;
            let mut right = 0;

            for i in (0..y).rev() {
                up += 1;
                if map[i][x] >= map[y][x] {
                    break;
                }
            }

            for i in y + 1..map.len() {
                down += 1;
                if map[i][x] >= map[y][x] {
                    break;
                }
            }

            for i in (0..x).rev() {
                left += 1;
                if map[y][i] >= map[y][x] {
                    break;
                }
            }

            for i in x + 1..map.len() {
                right += 1;
                if map[y][i] >= map[y][x] {
                    break;
                }
            }

            let scenic_score = up * down * left * right;

            if scenic_score > highest_scenic_score {
                highest_scenic_score = scenic_score;
            }
        }
    }
    highest_scenic_score
}
