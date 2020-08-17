(defun isPrime (arg)
    (if (<= arg 1) (return-from IsPrime 0))
    (loop for i from 2 to (- arg 1)
        do (
            if (= (mod arg i) 0) (return-from IsPrime 0)
        )
    )
    (return-from IsPrime 1)
)

(defun flatList (obj)
  (let (result)
    (labels ((grep (obj)
               (cond ((null obj) nil)
                     ((atom obj) (push obj result))
                     (t (grep (rest obj))
                        (grep (first obj))))))
      (grep obj)
      result)
    )
)


(defun isEven (arg)
    (if (= (mod arg 2) 0) (return-from isEven 1) (return-from isEven 0))
)


(defun numberOfPrimes (list)
    (setq count 0)
    (dolist (num (FlatList list))
        (if (= (IsPrime num) 1) (setq count (+ count 1)))
    )
    (return-from NumberOfPrimes count)
)

(defun even (list)
    (setq result '())
    (dolist (num (FlatList list))
        (if (= (isEven num) 1) (setq result (append result (list num))))
    )
    (print result)
    (return-from even result)
)

(defun sumIfNot (list1 list2)
    (setq sum 0)
    (setq flist1 (FlatList list1))  
    (setq flist2 (FlatList list2))
    (dolist (num flist2)
        (setq flag 1)
        (dolist (i flist1)
            (if (= num i) (setq flag 0))
        )
        (if (= flag 1) (setq sum (+ sum num)))
    )
    (print sum)
    (return-from sumIfNot sum)
)

