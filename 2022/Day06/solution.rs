use std::{
    collections::HashSet,
    fs::File,
    io::{BufRead, BufReader},
};

fn main() {
    let file_path = "input.txt";
    let input = get_input(file_path);

    println!("{}", part_one(&input));
}

fn part_one(input: &Vec<String>) -> usize {
    let start_marker_length = 4;
    let message = input[0].clone();
    return get_end_index_of_first_various_substring(message, start_marker_length);
}

fn get_input(file_path: &str) -> Vec<String> {
    let file = File::open(file_path).unwrap();
    let reader = BufReader::new(file);
    reader.lines().map(|line| line.unwrap()).collect()
}

fn get_end_index_of_first_various_substring(message: String, substring_length: usize) -> usize {
    for (index, _) in message.chars().enumerate() {
        let substring = &message[index..index + substring_length];
        let mut set = HashSet::new();

        for ch in substring.chars() {
            set.insert(ch);
        }

        if set.len() == substring_length {
            return index + substring_length;
        }
    }
    return 0;
}
