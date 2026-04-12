let contains = (s: string, sub: string): bool => {
  let lenSub = String.length(sub);
  let lenS = String.length(s);
  let rec aux = (i: int) =>
    if (i > lenS - lenSub) {
      false;
    } else if (String.sub(s, i, lenSub) == sub) {
      true;
    } else {
      aux(i + 1);
    };
  lenSub <= lenS && aux(0);
};

let testScenario = (scenario: string) =>
  Alcotest.test_case(scenario, `Quick, () => {
    let cmd = "../NativeRenderer.exe " ++ scenario;
    let ic = Unix.open_process_in(cmd);
    let output = ref("");
    let rec readAll = () =>
      switch (input_line(ic)) {
      | line =>
        output := output^ ++ line ++ "\n";
        readAll();
      | exception End_of_file => ()
      };
    readAll();
    let status = Unix.close_process_in(ic);
    switch (status) {
    | WEXITED(0) => ()
    | WEXITED(code) =>
      Alcotest.fail("NativeRenderer exited with code " ++ string_of_int(code))
    | WSIGNALED(sig_) =>
      Alcotest.fail("NativeRenderer killed by signal " ++ string_of_int(sig_))
    | WSTOPPED(sig_) =>
      Alcotest.fail("NativeRenderer stopped by signal " ++ string_of_int(sig_))
    };
    Alcotest.check(Alcotest.bool)("Output contains RENDER_START", true, contains(output^, "RENDER_START"));
    Alcotest.check(Alcotest.bool)("Output contains rdp-root", true, contains(output^, "rdp-root"));
  });

let () =
  Alcotest.run(
    "Native Renderer Tests",
    [
      (
        "scenarios",
        Array.to_list(Array.map(testScenario, Scenario.all)),
      ),
    ],
  );
