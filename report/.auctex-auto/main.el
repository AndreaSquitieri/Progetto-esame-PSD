(TeX-add-style-hook
 "main"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("scrartcl" "11pt")))
   (TeX-run-style-hooks
    "latex2e"
    "structure"
    "scrartcl"
    "scrartcl11"
    "listings"
    "xcolor"))
 :latex)

