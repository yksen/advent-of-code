use std::{fs::File, io::BufRead};

fn main() {
    let input_path = "input.txt";

    part_one(input_path);
    part_two(input_path);
}

fn part_one(input_path: &str) {
    let file = File::open(input_path).unwrap();
    let reader = std::io::BufReader::new(file);

    let mut total = 0;
    for line in reader.lines() {
        let line = line.unwrap();
        let elves: Vec<&str> = line.split(",").collect();
        let first_elf: Vec<u64> = elves[0].split("-").map(|x| x.parse().unwrap()).collect();
        let second_elf: Vec<u64> = elves[1].split("-").map(|x| x.parse().unwrap()).collect();

        if first_elf[0] <= second_elf[0] && first_elf[1] >= second_elf[1]
            || second_elf[0] <= first_elf[0] && second_elf[1] >= first_elf[1]
        {
            total += 1;
        }
    }
    println!("{}", total);
}

fn part_two(input_path: &str) {
    let file = File::open(input_path).unwrap();
    let reader = std::io::BufReader::new(file);

    let mut total = 0;
    for line in reader.lines() {
        let line = line.unwrap();
        let elves: Vec<&str> = line.split(",").collect();
        let first_elf: Vec<u64> = elves[0].split("-").map(|x| x.parse().unwrap()).collect();
        let second_elf: Vec<u64> = elves[1].split("-").map(|x| x.parse().unwrap()).collect();

        if first_elf[1] >= second_elf[0] && first_elf[0] <= second_elf[1] {
            total += 1;
        }
    }
    println!("{}", total);
}
