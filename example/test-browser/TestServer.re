open Js.Promise;

type response;
type childProcess;
type spawnOptions;

type t = {
  baseUrl: string,
  process: childProcess,
};

[@mel.module "node:child_process"]
external spawn:
  (string, array(string), spawnOptions) => childProcess = "spawn";

[@mel.obj]
external makeSpawnOptions:
  (~cwd: string, ~stdio: string, unit) => spawnOptions = "";

[@mel.scope "process"]
external cwd: unit => string = "cwd";

external fetchUrl: string => Js.Promise.t(response) = "fetch";

[@mel.get]
external responseOk: response => bool = "ok";

[@mel.send]
external kill: (childProcess, string) => bool = "kill";

[@mel.module "node:timers/promises"]
external sleep: int => Js.Promise.t(unit) = "setTimeout";

let rec waitForReady = (~url: string, ~attempts: int, ()) =>
  if (attempts <= 0) {
    reject(Failure("Timed out waiting for server at " ++ url));
  } else {
    fetchUrl(url)
    |> then_(response =>
         if (responseOk(response)) {
           resolve();
         } else {
           sleep(200) |> then_(_ => waitForReady(~url, ~attempts=attempts - 1, ()));
         }
       )
    |> catch(_error =>
         sleep(200) |> then_(_ => waitForReady(~url, ~attempts=attempts - 1, ()))
       );
  };

let start = (~port: int=8080, ~rootDir: string, ()) => {
  let process =
    spawn(
      "python3",
      [|"-m", "http.server", string_of_int(port), "--directory", rootDir|],
      makeSpawnOptions(~cwd=cwd(), ~stdio="inherit", ()),
    );

  waitForReady(~url="http://127.0.0.1:" ++ string_of_int(port) ++ "/", ~attempts=50, ())
  |> then_(_ => resolve({baseUrl: "http://127.0.0.1:" ++ string_of_int(port), process}));
};

let stop = (server: t) => {
  let _ = kill(server.process, "SIGTERM");
  sleep(200);
};
