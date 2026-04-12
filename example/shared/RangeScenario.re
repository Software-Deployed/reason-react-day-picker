type testConfig = {
  name: string,
  mode: string,
  rangeFrom: option(Js.Date.t),
  rangeTo: option(Js.Date.t),
};

let makeDate = (~year: int, ~month: int, ~day: int): Js.Date.t =>
  Js.Date.make(
    ~year=float_of_int(year),
    ~month=float_of_int(month),
    ~date=float_of_int(day),
    ~hours=12.0,
    ~minutes=0.0,
    ~seconds=0.0,
    (),
  );

let today = makeDate(~year=2026, ~month=2, ~day=21);
let tomorrow = makeDate(~year=2026, ~month=2, ~day=22);
let nextWeek = makeDate(~year=2026, ~month=2, ~day=28);

let all = [|
  "range-same-day",
  "range-multi-day",
  "range-start-only",
  "range-end-only",
|];

let byName = (name: string): testConfig => {
  let (rangeFrom, rangeTo) =
    switch (name) {
    | "range-same-day" => (Some(today), Some(today))
    | "range-multi-day" => (Some(today), Some(tomorrow))
    | "range-start-only" => (Some(today), None)
    | "range-end-only" => (None, Some(today))
    | _ => (Some(today), Some(tomorrow))
    };
  {name, mode: "range", rangeFrom, rangeTo};
};

let current = (): testConfig => {
  let name =
    if (Array.length(Sys.argv) > 1) {
      let candidate = Sys.argv[Array.length(Sys.argv) - 1];
      if (Array.exists((value) => value == candidate, all)) {
        candidate;
      } else {
        "range-same-day";
      };
    } else {
      "range-same-day";
    };
  byName(name);
};
