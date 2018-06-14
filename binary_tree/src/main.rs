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
    left: Option<Box<NodeTag>>,
    right: Option<Box<NodeTag>>,
    t: Type
}

impl NodeTag {
    fn new(number: f32) -> NodeTag {
        NodeTag {
            number: number,
            left: None,
            right: None,
            t: Type::NUM
        }
    }

    fn new_type(t: Type) -> NodeTag {
        NodeTag {
            number: 0.0,
            left: None,
            right: None,
            t: t
        }
    }
}

fn parse(s: &String) -> NodeTag {
    let mut chars = s.chars();
    while let Some(c) = chars.next() {
        if c == ' ' {
            continue;
        }

        if c.is_digit(10) {
            println!("is digit! {}", c);
            if let Some(d) = c.to_digit(10) {
                return NodeTag::new(d as f32);
            } else {
                panic!("Failed in char to digit!");
            }
        } else {
            let mut n = NodeTag::new_type(Type::ADD);
            match c {
                '+' => n.t = Type::ADD,
                '-' => n.t = Type::SUB,
                '*' => n.t = Type::MUL,
                '/' => n.t = Type::DIV,
                _ => n.t = Type::ADD
            };

            return n;
        }
    }

    return NodeTag::new(1.0);
}

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        println!("Need more args!");
        return
    }
    println!("{}", args[1]);
    // let expression = &args[1];
    parse(&args[1]);

}
