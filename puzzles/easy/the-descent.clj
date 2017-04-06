;; https://www.codingame.com/ide/puzzle/the-descent
;; Xavier Morel - 2016-03-12

(ns Player
    (:gen-class))
    ; Auto-generated code below aims at helping you parse
    ; the standard input according to the problem statement.

(defn -main [& args]
  (while true
    (def maxValue 0)
    (def maxRange 0)
    (loop [i 8]
          (when (> i 0)
            (let [mountainH (read)]
                 (when (> mountainH maxValue)
                   (def maxValue mountainH)
                   (def maxRange (- 8 i))
                   )
                 (recur (dec i)))))
                                        ; (binding [*out* *err*]
                                        ;   (println "Debug messages..."))
                                        ; The number of the mountain to fire on.
    (println maxRange)))
