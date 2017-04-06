;; https://www.codingame.com/ide/puzzle/power-of-thor-episode-1
;; Xavier Morel - 2016-03-12

(ns Player
    (:gen-class))

; Auto-generated code below aims at helping you parse
; the standard input according to the problem statement.
; ---
; Hint: You can use the debug stream to print initialTX and initialTY, if Thor seems not follow your orders.

(defn -main [& args]
  (let [lightX (read) lightY (read) initialTX (read) initialTY (read)]
     ; lightX: the X position of the light of power
     ; lightY: the Y position of the light of power
     ; initialTX: Thor's starting X position
     ; initialTY: Thor's starting Y position
       (def thorX initialTX)
       (def thorY initialTY)
       (while true
         (let [remainingTurns (read)]
              (cond
               (< lightY thorY) (do (print "N") (def thorY (- thorY 1)))
               (> lightY thorY) (do (print "S") (def thorY (+ thorY 1))))
              (cond
               (< lightX thorX) (do (print "W") (def thorX (- thorX 1)))
               (> lightX thorX) (do (print "E") (def thorX (+ thorX 1)))
               )
              (println "")
              ; (binding [*out* *err*]
              ; (println "Debug messages..."))

              ))))
