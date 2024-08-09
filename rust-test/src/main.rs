
fn foo(str: &str) {
    println!("{str}");
}

fn main() {
    println!("Hello, world!");
    let c1: i32 = 1;
    let c2 = c1;
    println!("{}", c2);
    
    let name = String::from("value c++");

    let name2 = "Rust".to_string();

    let str3 = "hello".to_owned();

    let new_name = name.replace("c++", "cpp");

    println!("{name} {name2} {str3}");

    foo(&new_name);

}
