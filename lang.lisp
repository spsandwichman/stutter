(import t )

(fun indexof (l item) (
    cond (
        ((is-nil l)         nil)
        ((eq (first l) item)  0)
        (true               (+ 1 (indexof (rest l) item))))))

(fun nth (i l) (
    cond (
        ((is-nil l) nil)
        ((eq i 0)   (car l))
        (true       (nth (- i 1) (cdr l))))))

(fun set-elem (i l item) (
    cond (
        ((is-nil l) nil)
        ((eq i 0)   (set (car l) item))
        (true       (set-elem (- index 1) (rest l) item)))))