type browserType;
type browser;
type page;
type browserContext;

type launchOptions;

[@mel.obj]
external makeLaunchOptions: (~headless: bool=?, unit) => launchOptions = "";

[@mel.module "@playwright/test"]
external chromium: browserType = "chromium";

[@mel.send]
external launch: (browserType, launchOptions) => Js.Promise.t(browser) = "launch";

[@mel.send]
external newPage: browser => Js.Promise.t(page) = "newPage";

[@mel.send]
external goto: (page, string) => Js.Promise.t(Js.Nullable.t('a)) = "goto";

[@mel.send]
external title: page => Js.Promise.t(string) = "title";

[@mel.send]
external textContent: (page, string) => Js.Promise.t(Js.Nullable.t(string)) = "textContent";

[@mel.send]
external waitForSelector: (page, string) => Js.Promise.t(Js.Nullable.t('a)) = "waitForSelector";

[@mel.send]
external click: (page, string) => Js.Promise.t(unit) = "click";

[@mel.send]
external close: browser => Js.Promise.t(unit) = "close";

[@mel.send]
external evaluateString: (page, string) => Js.Promise.t(string) = "evaluate";

[@mel.scope "process"]
external cwd: unit => string = "cwd";
