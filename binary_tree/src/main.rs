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

static mut i: usize = 0;

unsafe fn parse(s: &String) -> Option<Box<NodeTag>> {
    let mut bytes = s.as_bytes();
    if i >= s.len() {
        return None;
    }
    let c = bytes[i] as char;

    if c == ' ' {
        i = i + 1;
        return parse(s);
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
            _ => n.t = Type::ADD
        };

        i = i + 1;
        n.left = parse(s);
        if n.left.is_none() {
            return None;
        }

        i = i + 1;
        n.right = parse(s);
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
    // let expression = &args[1];
    // i = 0;
    unsafe {
        parse(&args[1]);
    }

}
