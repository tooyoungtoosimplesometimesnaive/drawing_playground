use std::env;

enum Type {
    NUM,
    ADD,
    SUB,
    MUL,
    DIV
}

struct NodeTag {
    number: f32,
    children: [Box<NodeTag>; 2]
}

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        println!("Need more args!");
        return
    }
    println!("{}", args[1]);
    let expression = &args[1];

    let mut chars = expression.chars();
    while let Some(c) = chars.next() {
        if c == ' ' {
            println!("Whitespace");
            continue;
        }
        println!("{}", c);
    }

    println!("Hello, world!");
}
