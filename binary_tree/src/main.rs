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


fn parse(bytes: &[u8], i: usize) -> Option<Box<NodeTag>> {
    if i >= bytes.len() {
        return None;
    }
    let c = bytes[i] as char;
    println!("the length = {}, char = {}", bytes.len(), c);

    if c == ' ' {
        return parse(bytes, i + 1);
    }

    let mut n = NodeTag::new_type(Type::NUM);

    if c.is_digit(10) {
        println!("is digit! {}", c);
        if let Some(d) = c.to_digit(10) {
            n.number = d as f32;
        } else {
            panic!("Failed in char to digit!");
        }
    } else {
        match c {
            '+' => n.t = Type::ADD,
            '-' => n.t = Type::SUB,
            '*' => n.t = Type::MUL,
            '/' => n.t = Type::DIV,
            _ => return None
        };

        n.left = parse(bytes, i + 1);
        if n.left.is_none() {
            return None;
        }

        n.right = parse(bytes, i + 1);
        if n.right.is_none() {
            return None;
        }
    }

    return Some(Box::new(n));
}

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        println!("Need more args!");
        return
    }
    println!("{}", args[1]);
    let bytes = args[1].as_bytes();
    if let Some(root) = parse(bytes, 0) {
        println!("There is a root!");
    } else {
        println!("Invalid input.");
    }

}
