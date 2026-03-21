(lang dune 3.20)

(name reason-react-day-picker)

(generate_opam_files true)

(source
 (github Software-Deployed/reason-react-day-picker))

(authors "Brian Kaplan <brian@softwaredeployed.com>")

(maintainers "Brian Kaplan <brian@softwaredeployed.com>")

(license MIT)

(using melange 0.1)

(package
 (name reason-react-day-picker)
 (synopsis "Melange bindings for react-day-picker")
 (description "Melange bindings for react-day-picker written in ReasonML")
  (depends
   ocaml
   melange
   reason
   melange-webapi
   reason-react-ppx
   reason-react
   server-reason-react
   (alcotest :with-test))
 (allow_empty)
 (tags
  ("melange" "reason" "bindings" "react-day-picker" "react")))

(pin
 (url "git+https://github.com/ml-in-barcelona/server-reason-react.git")
 (package
  (name server-reason-react)))

; See the complete stanza docs at https://dune.readthedocs.io/en/stable/reference/dune-project/index.html
