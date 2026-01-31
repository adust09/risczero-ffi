-- Fibonacci using only UInt32 (no Lean runtime dependency)
-- Uses partial for simplicity - generates pure C code

@[export lean_fibonacci]
partial def fibonacci (n : UInt32) : UInt32 :=
  if n ≤ 1 then n
  else
    let rec loop (i curr prev : UInt32) : UInt32 :=
      if i > n then curr
      else loop (i + 1) (prev + curr) curr
    loop 2 1 0

def main : IO Unit :=
  IO.println s!"fib(10) = {fibonacci 10}"
