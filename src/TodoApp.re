type item = {
  title: string,
  completed: bool
};

type state = {
  items: list(item),
};

type action =
  | AddItem;

let component = ReasonReact.reducerComponent("TodoApp");/*ReasonReact.statelessComponent("TodoApp");*/
let str = ReasonReact.stringToElement;

module TodoItem = {
  let component = ReasonReact.statelessComponent("TodoItem");
  let make = (~item, children) => {
    ...component,
    render: (self) => 
      <div className="item">
        <input
          _type="checkbox"
          checked=(Js.Boolean.to_js_boolean(item.completed))
        />
        (str(item.title))
      </div>
  };
};

let newItem = () => {title: "Click a button", completed: true};

let make = (children) => {
  ...component,
  initialState: () => {
    items: [{title: "Write some things to do", completed:false}]
  },
  reducer: (action, state) =>
    switch action {
      | AddItem => ReasonReact.Update({items: [newItem(), ...state.items]})
    },
  render: ({state: {items}, reduce}) => {
    let numItems = List.length(items);
    let num = numItems > 1 ? "items" : "item";
    <div className="app">
      <div className="title"> (str("What to do"))
      <button onClick=(reduce((_evt) => AddItem))>
        (str("Add something"))
      </button> 
      </div>
      <div className="items"> (ReasonReact.arrayToElement(Array.of_list(
        List.map((item) => <TodoItem item />, items)
      ))) </div>
      <div className="footer">(str(string_of_int(numItems) ++ " " ++ num))</div>
    </div>
  }
};

