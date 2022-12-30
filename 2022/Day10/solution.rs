use std::{
    fs::File,
    io::{BufRead, BufReader},
};
fn main() {
    solve_puzzle("input.txt");
}

fn solve_puzzle(file_path: &str) {
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

    let max_cycles = 6 * 40;
    let mut current_cycle: i32 = 0;
    let mut i = 0;
    let mut register: i32 = 1;
    let mut sum: i32 = 0;
    while current_cycle < max_cycles {
        print_pixel(register, current_cycle);

        if (21 + current_cycle) % 40 == 0 {
            sum += register * (current_cycle + 1);
        }

        current_cycle += 1;
        if instructions[i] != 0 {
            print_pixel(register, current_cycle);
            if (21 + current_cycle) % 40 == 0 {
                sum += register * (current_cycle + 1);
            }
            if current_cycle % 40 == 0 {
                println!();
            }
            register += instructions[i];
            current_cycle += 1;
        }
        i += 1;

        if current_cycle % 40 == 0 {
            println!();
        }
    }
    println!("{}", sum)
}

fn print_pixel(register: i32, current_cycle: i32) {
    if (current_cycle % 40 - register).abs() <= 1 {
        print!("#");
    } else {
        print!(".");
    }
}
