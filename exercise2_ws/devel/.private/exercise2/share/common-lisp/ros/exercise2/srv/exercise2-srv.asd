
(cl:in-package :asdf)

(defsystem "exercise2-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :exercise2-msg
)
  :components ((:file "_package")
    (:file "Service" :depends-on ("_package_Service"))
    (:file "_package_Service" :depends-on ("_package"))
  ))