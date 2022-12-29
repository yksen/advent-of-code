use std::{
    fs::File,
    io::{BufRead, BufReader},
};
fn main() {
    part_one("input.txt");
}

fn part_one(file_path: &str) {
    let file = File::open(file_path).unwrap();
    let reader = BufReader::new(file);
    let mut instructions: Vec<i32> = Vec::new();
    for line in reader.lines() {
        let line = line.unwrap();
        let values: Vec<&str> = line.split(' ').collect();
        if values.len() == 2 {
            let value: i32 = line.split(' ').nth(1).unwrap().parse().unwrap();
            instructions.push(value);
        } else {
            instructions.push(0);
        }
    }

    let mut current_cycle: i32 = 1;
    let mut register: i32 = 1;
    let mut sum: i32 = 0;
    let mut i = 0;
    while i < instructions.len() {
        if instructions[i] == 0 {
            current_cycle += 1;
        } else {
            current_cycle += 1;
            if (20 + current_cycle) % 40 == 0 {
                sum += register * current_cycle;
            }
            current_cycle += 1;
            register += instructions[i];
        }
        if (20 + current_cycle) % 40 == 0 {
            sum += register * current_cycle;
        }
        i += 1;
    }
    println!("{}", sum)
}
