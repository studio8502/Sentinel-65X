(define memories '(

        (memory HighCode
                (address (#x400000 . #x47FFFF))
                (type rom)
        )

        (memory HighData
                (address (#x010000 . #x07FFFF))
                (section heap)
                (type ram)
        )

        (memory LowCode
                (address (#x00E000 . #x00FFFF))
                (section code)
                (section cdata)
                (section switch)
        )

        (memory IOSpace
                (address (#x00DF00 . #x00DFFF))
                (section (VERAIOPort #x00DF00))
        )

        (memory LowData
                (address (#x001000 . #x00DEFF))
                (section near)
                (section data)
                (section znear)
                (section zdata)
        )

        (memory stack
                (address (#x000200 . #x000FFF))
                (section (stack #x00200))
                (section (cstack #x00400))
        )

        (memory DirectPage
                (address (#x000000 . #x0000FF))
                (section
                        (registers #x000004)
                        (ztiny)
                )
        )

        (block cstack (size #x400))               ; C stack size

        (block stack  (size #x200))               ; machine stack size

        (block heap  (size #x2000))

        (base-address _DirectPageStart DirectPage 0)

        (base-address _NearBaseAddress LowData    0)
))
