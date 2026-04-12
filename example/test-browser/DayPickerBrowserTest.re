open Js.Promise;

let run = () => {
  let launchOptions = Playwright.makeLaunchOptions(~headless=true, ());

  let serverRoot = Playwright.cwd();

  TestServer.start(~port=9876, ~rootDir=serverRoot, ())
  |> then_(server =>
       Playwright.chromium
       ->Playwright.launch(launchOptions)
       |> then_(browser =>
            browser
            ->Playwright.newPage
            |> then_(page =>
                 page
                 ->Playwright.goto(server.baseUrl ++ "/example/test-browser/index.html")
                 |> then_(_ => {
                      Js.log("Page loaded, waiting for calendar...");
                      page->Playwright.waitForSelector(".rdp-root");
                    })
                 |> then_(_ => page->Playwright.title)
                 |> then_(title =>
                      BrowserTestUtils.assertContains(
                        ~label="Page title",
                        ~expected="react-day-picker Browser Test",
                        title,
                      )
                    )
                 |> then_(_ => page->Playwright.waitForSelector(".rdp-month_caption"))
                 |> then_(_ => page->Playwright.waitForSelector(".rdp-day"))
                 |> then_(_ => page->Playwright.waitForSelector(".rdp-weekday"))
                 |> then_(_ => BrowserTestUtils.bodyText(page))
                 |> then_(body =>
                      BrowserTestUtils.assertContains(
                        ~label="Footer text",
                        ~expected="Browser test sample",
                        body,
                      )
                      |> then_(_ =>
                           BrowserTestUtils.assertContains(
                             ~label="Weekday header",
                             ~expected="Su",
                             body,
                           )
                         )
                    )
                 |> then_(_ => browser->Playwright.close)
                 |> then_(_ => {
                      ignore(TestServer.stop(server));
                      resolve();
                    })
               )
          )
     );
};

let () =
  run()
  |> then_(_ => {
       Js.log("DayPicker browser tests passed!");
       BrowserTestUtils.exitProcess(0);
       resolve();
     })
  |> catch(error => {
       Js.log2("DayPicker browser tests failed:", error);
       BrowserTestUtils.exitProcess(1);
       resolve();
     })
  |> ignore;
