function goPost(action)
{

  var obj1 = document.getElementById('starttime').value;
  var obj2 = document.getElementById('endtime').value;

  var form = document.createElement("form");
  form.setAttribute("charset", "UTF-8");
  form.setAttribute("method", "Post"); // Get 또는 Post 입력
  form.setAttribute("action", action);

  var hiddenField = document.createElement("input");
  hiddenField.setAttribute("name", "starttime");
  hiddenField.setAttribute("value", obj1);
  form.appendChild(hiddenField);

  var hiddenField = document.createElement("input");
  hiddenField.setAttribute("name", "endtime");
  hiddenField.setAttribute("value", obj2);
  form.appendChild(hiddenField);

  document.body.appendChild(form);

  form.submit();
}

function goPostDel(id)
{
  var form = document.createElement("form");
  form.setAttribute("charset", "UTF-8");
  form.setAttribute("method", "Post"); // Get 또는 Post 입력
  form.setAttribute("action", 'delete');

  var hiddenField = document.createElement("input");
  hiddenField.setAttribute("name", "id");
  hiddenField.setAttribute("value", id);
  form.appendChild(hiddenField);

  document.body.appendChild(form);

  form.submit();
}

function goPostUpdate(id)
{
  console.log("u_name"+id);
  var obj1 = document.getElementById("u_name"+id).value;
  var obj2 = document.getElementById("u_phone"+id).value;
  var obj3 = document.getElementById("u_email"+id).value;
  var obj4 = document.getElementById("u_group"+id).value;
  var obj5 = document.getElementById("u_birth"+id).value;

  var form = document.createElement("form");
  form.setAttribute("charset", "UTF-8");
  form.setAttribute("method", "Post"); // Get 또는 Post 입력
  form.setAttribute("action", 'update');

  var hiddenField = document.createElement("input");
  hiddenField.setAttribute("name", "name");
  hiddenField.setAttribute("value", obj1);
  form.appendChild(hiddenField);

  var hiddenField = document.createElement("input");
  hiddenField.setAttribute("name", "phone");
  hiddenField.setAttribute("value", obj2);
  form.appendChild(hiddenField);

  var hiddenField = document.createElement("input");
  hiddenField.setAttribute("name", "email");
  hiddenField.setAttribute("value", obj3);
  form.appendChild(hiddenField);

  var hiddenField = document.createElement("input");
  hiddenField.setAttribute("name", "group");
  hiddenField.setAttribute("value", obj4);
  form.appendChild(hiddenField);

  var hiddenField = document.createElement("input");
  hiddenField.setAttribute("name", "birth");
  hiddenField.setAttribute("value", obj5);
  form.appendChild(hiddenField);

  var hiddenField = document.createElement("input");
  hiddenField.setAttribute("name", "id");
  hiddenField.setAttribute("value", id);
  form.appendChild(hiddenField);

  document.body.appendChild(form);

  form.submit();
}
