import hashlib


def pwn():
    for a in range(97, 123):
        for b in range(97, 123):
            for c in range(97, 123):
                for d in range(97, 123):
                    for e in range(97, 123):
                        for f in range(97, 123):
                            string = chr(a) + chr(b) + chr(c) + chr(d) + chr(e) + chr(f)
                            hash_string = hashlib.md5()
                            hash_string.update(string.encode(encoding='UTF-8'))
                            hash_string = hash_string.hexdigest()
                            number = 0
                            low_cat = 0
                            for x in range(len(hash_string)):
                                if hash_string == "0":
                                    number = number + 1
                                    low_cat = low_cat + x
                            if 10 * number + low_cat == 403:
                                print(string)


def main():
    pwn()


if __name__ == '__main__':
    main()
