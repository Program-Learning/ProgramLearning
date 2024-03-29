use rand::Rng; //trait
use std::cmp::Ordering;
use std::io; // prelude
fn main() {
    println!("Guess the number");
    let secret_number = rand::thread_rng().gen_range(1..=100);
    // println!("the secret number is {}", secret_number);
    // std::io::stdin().read_line(&mut guess).expect("reading error");
    loop {
        println!("Guess a number:");
        let mut guess = String::new();
        io::stdin()
            .read_line(&mut guess)
            .expect("reading line error");
        let guess: u32 = match guess.trim().parse() {
            Ok(number) => number,
            Err(_) => continue,
        };
        println!("the number you guess is {}", guess);
        match guess.cmp(&secret_number) {
            Ordering::Less => println!("Too small!"), // arm
            Ordering::Greater => println!("Too big!"),
            Ordering::Equal => {
                println!("You win!");
                break;
            }
        }
    }
}
