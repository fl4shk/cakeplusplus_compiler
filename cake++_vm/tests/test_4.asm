[
	{
		"_func_name" : "main",
		"contents" : 
		[
			{
				"__iop" : "call",
				"args" : 
				[
					{
						"__op" : "call_with_ret",
						"_mm" : "u64",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "getline"
							},
							{
								"__op" : "real_address",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "ref_sym",
										"_mm" : "pointer",
										"_name" : "buf"
									}
								]
							}
						]
					}
				]
			},
			{
				"__iop" : "call",
				"args" : 
				[
					{
						"__op" : "call_with_ret",
						"_mm" : "u64",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "disp_str_as_numbers"
							},
							{
								"__op" : "real_address",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "ref_sym",
										"_mm" : "pointer",
										"_name" : "buf"
									}
								]
							}
						]
					}
				]
			}
		]
	},
	{
		"_func_name" : "getline",
		"contents" : 
		[
			{
				"__iop" : "st",
				"_mm" : "u64",
				"args" : 
				[
					{
						"__op" : "real_address",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "buf_len"
							}
						]
					},
					{
						"__op" : "len",
						"_mm" : "length",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "buf"
							}
						]
					}
				]
			},
			{
				"__iop" : "st",
				"_mm" : "u64",
				"args" : 
				[
					{
						"__op" : "real_address",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "i"
							}
						]
					},
					{
						"__op" : "const",
						"_immediate" : "0",
						"_mm" : "s64"
					}
				]
			},
			{
				"__iop" : "label",
				"_name" : "_0"
			},
			{
				"__iop" : "st",
				"_mm" : "u8",
				"args" : 
				[
					{
						"__op" : "real_address",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "char"
							}
						]
					},
					{
						"__op" : "syscall",
						"_mm" : "u8",
						"_syscall_shorthand_op" : "get_char"
					}
				]
			},
			{
				"__iop" : "jump",
				"args" : 
				[
					{
						"__op" : "if_then_else",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "binop",
								"_binop" : "cmp_ne",
								"_mm" : "s64",
								"args" : 
								[
									{
										"__op" : "ld",
										"_mm" : "u8",
										"args" : 
										[
											{
												"__op" : "real_address",
												"_mm" : "pointer",
												"args" : 
												[
													{
														"__op" : "ref_sym",
														"_mm" : "pointer",
														"_name" : "char"
													}
												]
											}
										]
									},
									{
										"__op" : "const",
										"_immediate" : "10",
										"_mm" : "s64"
									}
								]
							},
							{
								"__op" : "get_next_pc",
								"_mm" : "pointer"
							},
							{
								"__op" : "real_address",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "ref_lab",
										"_mm" : "pointer",
										"_name" : "_1"
									}
								]
							}
						]
					}
				]
			},
			{
				"__iop" : "st",
				"_mm" : "u8",
				"args" : 
				[
					{
						"__op" : "binop",
						"_binop" : "add",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "arr_data_address",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "deref",
										"_mm" : "pointer",
										"args" : 
										[
											{
												"__op" : "ref_sym",
												"_mm" : "pointer",
												"_name" : "buf"
											}
										]
									}
								]
							},
							{
								"__op" : "binop",
								"_binop" : "mul",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "const",
										"_immediate" : "1",
										"_mm" : "length"
									},
									{
										"__op" : "ld",
										"_mm" : "u64",
										"args" : 
										[
											{
												"__op" : "real_address",
												"_mm" : "pointer",
												"args" : 
												[
													{
														"__op" : "ref_sym",
														"_mm" : "pointer",
														"_name" : "i"
													}
												]
											}
										]
									}
								]
							}
						]
					},
					{
						"__op" : "ld",
						"_mm" : "u8",
						"args" : 
						[
							{
								"__op" : "real_address",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "ref_sym",
										"_mm" : "pointer",
										"_name" : "char"
									}
								]
							}
						]
					}
				]
			},
			{
				"__iop" : "label",
				"_name" : "_1"
			},
			{
				"__iop" : "st",
				"_mm" : "u64",
				"args" : 
				[
					{
						"__op" : "real_address",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "i"
							}
						]
					},
					{
						"__op" : "binop",
						"_binop" : "add",
						"_mm" : "u64",
						"args" : 
						[
							{
								"__op" : "ld",
								"_mm" : "u64",
								"args" : 
								[
									{
										"__op" : "real_address",
										"_mm" : "pointer",
										"args" : 
										[
											{
												"__op" : "ref_sym",
												"_mm" : "pointer",
												"_name" : "i"
											}
										]
									}
								]
							},
							{
								"__op" : "const",
								"_immediate" : "1",
								"_mm" : "s64"
							}
						]
					}
				]
			},
			{
				"__iop" : "jump",
				"args" : 
				[
					{
						"__op" : "if_then_else",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "binop",
								"_binop" : "log_and",
								"_mm" : "s64",
								"args" : 
								[
									{
										"__op" : "binop",
										"_binop" : "cmp_ne",
										"_mm" : "s64",
										"args" : 
										[
											{
												"__op" : "ld",
												"_mm" : "u8",
												"args" : 
												[
													{
														"__op" : "real_address",
														"_mm" : "pointer",
														"args" : 
														[
															{
																"__op" : "ref_sym",
																"_mm" : "pointer",
																"_name" : "char"
															}
														]
													}
												]
											},
											{
												"__op" : "const",
												"_immediate" : "10",
												"_mm" : "s64"
											}
										]
									},
									{
										"__op" : "binop",
										"_binop" : "cmp_lt",
										"_mm" : "s64",
										"args" : 
										[
											{
												"__op" : "binop",
												"_binop" : "add",
												"_mm" : "s64",
												"args" : 
												[
													{
														"__op" : "ld",
														"_mm" : "u64",
														"args" : 
														[
															{
																"__op" : "real_address",
																"_mm" : "pointer",
																"args" : 
																[
																	{
																		"__op" : "ref_sym",
																		"_mm" : "pointer",
																		"_name" : "i"
																	}
																]
															}
														]
													},
													{
														"__op" : "const",
														"_immediate" : "1",
														"_mm" : "s64"
													}
												]
											},
											{
												"__op" : "ld",
												"_mm" : "u64",
												"args" : 
												[
													{
														"__op" : "real_address",
														"_mm" : "pointer",
														"args" : 
														[
															{
																"__op" : "ref_sym",
																"_mm" : "pointer",
																"_name" : "buf_len"
															}
														]
													}
												]
											}
										]
									}
								]
							},
							{
								"__op" : "real_address",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "ref_lab",
										"_mm" : "pointer",
										"_name" : "_0"
									}
								]
							},
							{
								"__op" : "get_next_pc",
								"_mm" : "pointer"
							}
						]
					}
				]
			},
			{
				"__iop" : "st",
				"_mm" : "u8",
				"args" : 
				[
					{
						"__op" : "binop",
						"_binop" : "add",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "arr_data_address",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "deref",
										"_mm" : "pointer",
										"args" : 
										[
											{
												"__op" : "ref_sym",
												"_mm" : "pointer",
												"_name" : "buf"
											}
										]
									}
								]
							},
							{
								"__op" : "binop",
								"_binop" : "mul",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "const",
										"_immediate" : "1",
										"_mm" : "length"
									},
									{
										"__op" : "ld",
										"_mm" : "u64",
										"args" : 
										[
											{
												"__op" : "real_address",
												"_mm" : "pointer",
												"args" : 
												[
													{
														"__op" : "ref_sym",
														"_mm" : "pointer",
														"_name" : "i"
													}
												]
											}
										]
									}
								]
							}
						]
					},
					{
						"__op" : "const",
						"_immediate" : "0",
						"_mm" : "s64"
					}
				]
			},
			{
				"__iop" : "return_expr",
				"args" : 
				[
					{
						"__op" : "ld",
						"_mm" : "u64",
						"args" : 
						[
							{
								"__op" : "real_address",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "ref_sym",
										"_mm" : "pointer",
										"_name" : "i"
									}
								]
							}
						]
					}
				]
			}
		]
	},
	{
		"_func_name" : "disp_str",
		"contents" : 
		[
			{
				"__iop" : "st",
				"_mm" : "u64",
				"args" : 
				[
					{
						"__op" : "real_address",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "buf_len"
							}
						]
					},
					{
						"__op" : "len",
						"_mm" : "length",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "str"
							}
						]
					}
				]
			},
			{
				"__iop" : "st",
				"_mm" : "u64",
				"args" : 
				[
					{
						"__op" : "real_address",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "i"
							}
						]
					},
					{
						"__op" : "const",
						"_immediate" : "0",
						"_mm" : "s64"
					}
				]
			},
			{
				"__iop" : "label",
				"_name" : "_0"
			},
			{
				"__iop" : "jump",
				"args" : 
				[
					{
						"__op" : "if_then_else",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "binop",
								"_binop" : "log_and",
								"_mm" : "s64",
								"args" : 
								[
									{
										"__op" : "binop",
										"_binop" : "cmp_lt",
										"_mm" : "u64",
										"args" : 
										[
											{
												"__op" : "ld",
												"_mm" : "u64",
												"args" : 
												[
													{
														"__op" : "real_address",
														"_mm" : "pointer",
														"args" : 
														[
															{
																"__op" : "ref_sym",
																"_mm" : "pointer",
																"_name" : "i"
															}
														]
													}
												]
											},
											{
												"__op" : "ld",
												"_mm" : "u64",
												"args" : 
												[
													{
														"__op" : "real_address",
														"_mm" : "pointer",
														"args" : 
														[
															{
																"__op" : "ref_sym",
																"_mm" : "pointer",
																"_name" : "buf_len"
															}
														]
													}
												]
											}
										]
									},
									{
										"__op" : "binop",
										"_binop" : "cmp_ne",
										"_mm" : "s64",
										"args" : 
										[
											{
												"__op" : "ld",
												"_mm" : "u8",
												"args" : 
												[
													{
														"__op" : "binop",
														"_binop" : "add",
														"_mm" : "pointer",
														"args" : 
														[
															{
																"__op" : "arr_data_address",
																"_mm" : "pointer",
																"args" : 
																[
																	{
																		"__op" : "deref",
																		"_mm" : "pointer",
																		"args" : 
																		[
																			{
																				"__op" : "ref_sym",
																				"_mm" : "pointer",
																				"_name" : "str"
																			}
																		]
																	}
																]
															},
															{
																"__op" : "binop",
																"_binop" : "mul",
																"_mm" : "pointer",
																"args" : 
																[
																	{
																		"__op" : "const",
																		"_immediate" : "1",
																		"_mm" : "length"
																	},
																	{
																		"__op" : "ld",
																		"_mm" : "u64",
																		"args" : 
																		[
																			{
																				"__op" : "real_address",
																				"_mm" : "pointer",
																				"args" : 
																				[
																					{
																						"__op" : "ref_sym",
																						"_mm" : "pointer",
																						"_name" : "i"
																					}
																				]
																			}
																		]
																	}
																]
															}
														]
													}
												]
											},
											{
												"__op" : "const",
												"_immediate" : "0",
												"_mm" : "s64"
											}
										]
									}
								]
							},
							{
								"__op" : "get_next_pc",
								"_mm" : "pointer"
							},
							{
								"__op" : "real_address",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "ref_lab",
										"_mm" : "pointer",
										"_name" : "_1"
									}
								]
							}
						]
					}
				]
			},
			{
				"__iop" : "syscall",
				"_syscall_shorthand_op" : "disp_char",
				"args" : 
				[
					{
						"__op" : "ld",
						"_mm" : "u8",
						"args" : 
						[
							{
								"__op" : "binop",
								"_binop" : "add",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "arr_data_address",
										"_mm" : "pointer",
										"args" : 
										[
											{
												"__op" : "deref",
												"_mm" : "pointer",
												"args" : 
												[
													{
														"__op" : "ref_sym",
														"_mm" : "pointer",
														"_name" : "str"
													}
												]
											}
										]
									},
									{
										"__op" : "binop",
										"_binop" : "mul",
										"_mm" : "pointer",
										"args" : 
										[
											{
												"__op" : "const",
												"_immediate" : "1",
												"_mm" : "length"
											},
											{
												"__op" : "ld",
												"_mm" : "u64",
												"args" : 
												[
													{
														"__op" : "real_address",
														"_mm" : "pointer",
														"args" : 
														[
															{
																"__op" : "ref_sym",
																"_mm" : "pointer",
																"_name" : "i"
															}
														]
													}
												]
											}
										]
									}
								]
							}
						]
					}
				]
			},
			{
				"__iop" : "st",
				"_mm" : "u64",
				"args" : 
				[
					{
						"__op" : "real_address",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "i"
							}
						]
					},
					{
						"__op" : "binop",
						"_binop" : "add",
						"_mm" : "u64",
						"args" : 
						[
							{
								"__op" : "ld",
								"_mm" : "u64",
								"args" : 
								[
									{
										"__op" : "real_address",
										"_mm" : "pointer",
										"args" : 
										[
											{
												"__op" : "ref_sym",
												"_mm" : "pointer",
												"_name" : "i"
											}
										]
									}
								]
							},
							{
								"__op" : "const",
								"_immediate" : "1",
								"_mm" : "s64"
							}
						]
					}
				]
			},
			{
				"__iop" : "jump",
				"args" : 
				[
					{
						"__op" : "ref_lab",
						"_mm" : "pointer",
						"_name" : "_0"
					}
				]
			},
			{
				"__iop" : "label",
				"_name" : "_1"
			},
			{
				"__iop" : "return_expr",
				"args" : 
				[
					{
						"__op" : "ld",
						"_mm" : "u64",
						"args" : 
						[
							{
								"__op" : "real_address",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "ref_sym",
										"_mm" : "pointer",
										"_name" : "i"
									}
								]
							}
						]
					}
				]
			}
		]
	},
	{
		"_func_name" : "disp_str_as_numbers",
		"contents" : 
		[
			{
				"__iop" : "st",
				"_mm" : "u64",
				"args" : 
				[
					{
						"__op" : "real_address",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "buf_len"
							}
						]
					},
					{
						"__op" : "len",
						"_mm" : "length",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "str"
							}
						]
					}
				]
			},
			{
				"__iop" : "st",
				"_mm" : "u64",
				"args" : 
				[
					{
						"__op" : "real_address",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "i"
							}
						]
					},
					{
						"__op" : "const",
						"_immediate" : "0",
						"_mm" : "s64"
					}
				]
			},
			{
				"__iop" : "label",
				"_name" : "_0"
			},
			{
				"__iop" : "jump",
				"args" : 
				[
					{
						"__op" : "if_then_else",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "binop",
								"_binop" : "log_and",
								"_mm" : "s64",
								"args" : 
								[
									{
										"__op" : "binop",
										"_binop" : "cmp_lt",
										"_mm" : "u64",
										"args" : 
										[
											{
												"__op" : "ld",
												"_mm" : "u64",
												"args" : 
												[
													{
														"__op" : "real_address",
														"_mm" : "pointer",
														"args" : 
														[
															{
																"__op" : "ref_sym",
																"_mm" : "pointer",
																"_name" : "i"
															}
														]
													}
												]
											},
											{
												"__op" : "ld",
												"_mm" : "u64",
												"args" : 
												[
													{
														"__op" : "real_address",
														"_mm" : "pointer",
														"args" : 
														[
															{
																"__op" : "ref_sym",
																"_mm" : "pointer",
																"_name" : "buf_len"
															}
														]
													}
												]
											}
										]
									},
									{
										"__op" : "binop",
										"_binop" : "cmp_ne",
										"_mm" : "s64",
										"args" : 
										[
											{
												"__op" : "ld",
												"_mm" : "u8",
												"args" : 
												[
													{
														"__op" : "binop",
														"_binop" : "add",
														"_mm" : "pointer",
														"args" : 
														[
															{
																"__op" : "arr_data_address",
																"_mm" : "pointer",
																"args" : 
																[
																	{
																		"__op" : "deref",
																		"_mm" : "pointer",
																		"args" : 
																		[
																			{
																				"__op" : "ref_sym",
																				"_mm" : "pointer",
																				"_name" : "str"
																			}
																		]
																	}
																]
															},
															{
																"__op" : "binop",
																"_binop" : "mul",
																"_mm" : "pointer",
																"args" : 
																[
																	{
																		"__op" : "const",
																		"_immediate" : "1",
																		"_mm" : "length"
																	},
																	{
																		"__op" : "ld",
																		"_mm" : "u64",
																		"args" : 
																		[
																			{
																				"__op" : "real_address",
																				"_mm" : "pointer",
																				"args" : 
																				[
																					{
																						"__op" : "ref_sym",
																						"_mm" : "pointer",
																						"_name" : "i"
																					}
																				]
																			}
																		]
																	}
																]
															}
														]
													}
												]
											},
											{
												"__op" : "const",
												"_immediate" : "0",
												"_mm" : "s64"
											}
										]
									}
								]
							},
							{
								"__op" : "get_next_pc",
								"_mm" : "pointer"
							},
							{
								"__op" : "real_address",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "ref_lab",
										"_mm" : "pointer",
										"_name" : "_1"
									}
								]
							}
						]
					}
				]
			},
			{
				"__iop" : "syscall",
				"_syscall_shorthand_op" : "disp_num",
				"args" : 
				[
					{
						"__op" : "ld",
						"_mm" : "u8",
						"args" : 
						[
							{
								"__op" : "binop",
								"_binop" : "add",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "arr_data_address",
										"_mm" : "pointer",
										"args" : 
										[
											{
												"__op" : "deref",
												"_mm" : "pointer",
												"args" : 
												[
													{
														"__op" : "ref_sym",
														"_mm" : "pointer",
														"_name" : "str"
													}
												]
											}
										]
									},
									{
										"__op" : "binop",
										"_binop" : "mul",
										"_mm" : "pointer",
										"args" : 
										[
											{
												"__op" : "const",
												"_immediate" : "1",
												"_mm" : "length"
											},
											{
												"__op" : "ld",
												"_mm" : "u64",
												"args" : 
												[
													{
														"__op" : "real_address",
														"_mm" : "pointer",
														"args" : 
														[
															{
																"__op" : "ref_sym",
																"_mm" : "pointer",
																"_name" : "i"
															}
														]
													}
												]
											}
										]
									}
								]
							}
						]
					}
				]
			},
			{
				"__iop" : "st",
				"_mm" : "u64",
				"args" : 
				[
					{
						"__op" : "real_address",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "i"
							}
						]
					},
					{
						"__op" : "binop",
						"_binop" : "add",
						"_mm" : "u64",
						"args" : 
						[
							{
								"__op" : "ld",
								"_mm" : "u64",
								"args" : 
								[
									{
										"__op" : "real_address",
										"_mm" : "pointer",
										"args" : 
										[
											{
												"__op" : "ref_sym",
												"_mm" : "pointer",
												"_name" : "i"
											}
										]
									}
								]
							},
							{
								"__op" : "const",
								"_immediate" : "1",
								"_mm" : "s64"
							}
						]
					}
				]
			},
			{
				"__iop" : "jump",
				"args" : 
				[
					{
						"__op" : "if_then_else",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "binop",
								"_binop" : "log_and",
								"_mm" : "s64",
								"args" : 
								[
									{
										"__op" : "binop",
										"_binop" : "cmp_lt",
										"_mm" : "u64",
										"args" : 
										[
											{
												"__op" : "ld",
												"_mm" : "u64",
												"args" : 
												[
													{
														"__op" : "real_address",
														"_mm" : "pointer",
														"args" : 
														[
															{
																"__op" : "ref_sym",
																"_mm" : "pointer",
																"_name" : "i"
															}
														]
													}
												]
											},
											{
												"__op" : "ld",
												"_mm" : "u64",
												"args" : 
												[
													{
														"__op" : "real_address",
														"_mm" : "pointer",
														"args" : 
														[
															{
																"__op" : "ref_sym",
																"_mm" : "pointer",
																"_name" : "buf_len"
															}
														]
													}
												]
											}
										]
									},
									{
										"__op" : "binop",
										"_binop" : "cmp_ne",
										"_mm" : "s64",
										"args" : 
										[
											{
												"__op" : "ld",
												"_mm" : "u8",
												"args" : 
												[
													{
														"__op" : "binop",
														"_binop" : "add",
														"_mm" : "pointer",
														"args" : 
														[
															{
																"__op" : "arr_data_address",
																"_mm" : "pointer",
																"args" : 
																[
																	{
																		"__op" : "deref",
																		"_mm" : "pointer",
																		"args" : 
																		[
																			{
																				"__op" : "ref_sym",
																				"_mm" : "pointer",
																				"_name" : "str"
																			}
																		]
																	}
																]
															},
															{
																"__op" : "binop",
																"_binop" : "mul",
																"_mm" : "pointer",
																"args" : 
																[
																	{
																		"__op" : "const",
																		"_immediate" : "1",
																		"_mm" : "length"
																	},
																	{
																		"__op" : "ld",
																		"_mm" : "u64",
																		"args" : 
																		[
																			{
																				"__op" : "real_address",
																				"_mm" : "pointer",
																				"args" : 
																				[
																					{
																						"__op" : "ref_sym",
																						"_mm" : "pointer",
																						"_name" : "i"
																					}
																				]
																			}
																		]
																	}
																]
															}
														]
													}
												]
											},
											{
												"__op" : "const",
												"_immediate" : "0",
												"_mm" : "s64"
											}
										]
									}
								]
							},
							{
								"__op" : "get_next_pc",
								"_mm" : "pointer"
							},
							{
								"__op" : "real_address",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "ref_lab",
										"_mm" : "pointer",
										"_name" : "_2"
									}
								]
							}
						]
					}
				]
			},
			{
				"__iop" : "call",
				"args" : 
				[
					{
						"__op" : "call_with_ret",
						"_mm" : "u8",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "disp_comma"
							}
						]
					}
				]
			},
			{
				"__iop" : "call",
				"args" : 
				[
					{
						"__op" : "call_with_ret",
						"_mm" : "u8",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "disp_space"
							}
						]
					}
				]
			},
			{
				"__iop" : "label",
				"_name" : "_2"
			},
			{
				"__iop" : "jump",
				"args" : 
				[
					{
						"__op" : "ref_lab",
						"_mm" : "pointer",
						"_name" : "_0"
					}
				]
			},
			{
				"__iop" : "label",
				"_name" : "_1"
			},
			{
				"__iop" : "call",
				"args" : 
				[
					{
						"__op" : "call_with_ret",
						"_mm" : "u8",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "disp_newline"
							}
						]
					}
				]
			},
			{
				"__iop" : "return_expr",
				"args" : 
				[
					{
						"__op" : "ld",
						"_mm" : "u64",
						"args" : 
						[
							{
								"__op" : "real_address",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "ref_sym",
										"_mm" : "pointer",
										"_name" : "i"
									}
								]
							}
						]
					}
				]
			}
		]
	},
	{
		"_func_name" : "disp_newline",
		"contents" : 
		[
			{
				"__iop" : "syscall",
				"_syscall_shorthand_op" : "disp_char",
				"args" : 
				[
					{
						"__op" : "const",
						"_immediate" : "10",
						"_mm" : "s64"
					}
				]
			}
		]
	},
	{
		"_func_name" : "disp_space",
		"contents" : 
		[
			{
				"__iop" : "syscall",
				"_syscall_shorthand_op" : "disp_char",
				"args" : 
				[
					{
						"__op" : "const",
						"_immediate" : "32",
						"_mm" : "s64"
					}
				]
			}
		]
	},
	{
		"_func_name" : "disp_comma",
		"contents" : 
		[
			{
				"__iop" : "syscall",
				"_syscall_shorthand_op" : "disp_char",
				"args" : 
				[
					{
						"__op" : "const",
						"_immediate" : "44",
						"_mm" : "s64"
					}
				]
			}
		]
	},
	{
		"_func_name" : "fun_func_a",
		"contents" : 
		[
			{
				"__iop" : "st",
				"_mm" : "u64",
				"args" : 
				[
					{
						"__op" : "real_address",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "i"
							}
						]
					},
					{
						"__op" : "const",
						"_immediate" : "0",
						"_mm" : "s64"
					}
				]
			},
			{
				"__iop" : "label",
				"_name" : "_0"
			},
			{
				"__iop" : "jump",
				"args" : 
				[
					{
						"__op" : "if_then_else",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "binop",
								"_binop" : "cmp_lt",
								"_mm" : "u64",
								"args" : 
								[
									{
										"__op" : "ld",
										"_mm" : "u64",
										"args" : 
										[
											{
												"__op" : "real_address",
												"_mm" : "pointer",
												"args" : 
												[
													{
														"__op" : "ref_sym",
														"_mm" : "pointer",
														"_name" : "i"
													}
												]
											}
										]
									},
									{
										"__op" : "len",
										"_mm" : "length",
										"args" : 
										[
											{
												"__op" : "ref_sym",
												"_mm" : "pointer",
												"_name" : "arr"
											}
										]
									}
								]
							},
							{
								"__op" : "get_next_pc",
								"_mm" : "pointer"
							},
							{
								"__op" : "real_address",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "ref_lab",
										"_mm" : "pointer",
										"_name" : "_1"
									}
								]
							}
						]
					}
				]
			},
			{
				"__iop" : "st",
				"_mm" : "s64",
				"args" : 
				[
					{
						"__op" : "binop",
						"_binop" : "add",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "arr_data_address",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "deref",
										"_mm" : "pointer",
										"args" : 
										[
											{
												"__op" : "ref_sym",
												"_mm" : "pointer",
												"_name" : "arr"
											}
										]
									}
								]
							},
							{
								"__op" : "binop",
								"_binop" : "mul",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "const",
										"_immediate" : "8",
										"_mm" : "length"
									},
									{
										"__op" : "ld",
										"_mm" : "u64",
										"args" : 
										[
											{
												"__op" : "real_address",
												"_mm" : "pointer",
												"args" : 
												[
													{
														"__op" : "ref_sym",
														"_mm" : "pointer",
														"_name" : "i"
													}
												]
											}
										]
									}
								]
							}
						]
					},
					{
						"__op" : "binop",
						"_binop" : "mul",
						"_mm" : "s64",
						"args" : 
						[
							{
								"__op" : "ld",
								"_mm" : "u64",
								"args" : 
								[
									{
										"__op" : "real_address",
										"_mm" : "pointer",
										"args" : 
										[
											{
												"__op" : "ref_sym",
												"_mm" : "pointer",
												"_name" : "i"
											}
										]
									}
								]
							},
							{
								"__op" : "const",
								"_immediate" : "8",
								"_mm" : "s64"
							}
						]
					}
				]
			},
			{
				"__iop" : "st",
				"_mm" : "u64",
				"args" : 
				[
					{
						"__op" : "real_address",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "i"
							}
						]
					},
					{
						"__op" : "binop",
						"_binop" : "add",
						"_mm" : "u64",
						"args" : 
						[
							{
								"__op" : "ld",
								"_mm" : "u64",
								"args" : 
								[
									{
										"__op" : "real_address",
										"_mm" : "pointer",
										"args" : 
										[
											{
												"__op" : "ref_sym",
												"_mm" : "pointer",
												"_name" : "i"
											}
										]
									}
								]
							},
							{
								"__op" : "const",
								"_immediate" : "1",
								"_mm" : "s64"
							}
						]
					}
				]
			},
			{
				"__iop" : "jump",
				"args" : 
				[
					{
						"__op" : "ref_lab",
						"_mm" : "pointer",
						"_name" : "_0"
					}
				]
			},
			{
				"__iop" : "label",
				"_name" : "_1"
			},
			{
				"__iop" : "return_expr",
				"args" : 
				[
					{
						"__op" : "ld",
						"_mm" : "u64",
						"args" : 
						[
							{
								"__op" : "real_address",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "ref_sym",
										"_mm" : "pointer",
										"_name" : "i"
									}
								]
							}
						]
					}
				]
			}
		]
	},
	{
		"_func_name" : "fun_func_b",
		"contents" : 
		[
			{
				"__iop" : "st",
				"_mm" : "u64",
				"args" : 
				[
					{
						"__op" : "real_address",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "i"
							}
						]
					},
					{
						"__op" : "const",
						"_immediate" : "0",
						"_mm" : "s64"
					}
				]
			},
			{
				"__iop" : "label",
				"_name" : "_0"
			},
			{
				"__iop" : "jump",
				"args" : 
				[
					{
						"__op" : "if_then_else",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "binop",
								"_binop" : "cmp_lt",
								"_mm" : "u64",
								"args" : 
								[
									{
										"__op" : "ld",
										"_mm" : "u64",
										"args" : 
										[
											{
												"__op" : "real_address",
												"_mm" : "pointer",
												"args" : 
												[
													{
														"__op" : "ref_sym",
														"_mm" : "pointer",
														"_name" : "i"
													}
												]
											}
										]
									},
									{
										"__op" : "len",
										"_mm" : "length",
										"args" : 
										[
											{
												"__op" : "ref_sym",
												"_mm" : "pointer",
												"_name" : "arr"
											}
										]
									}
								]
							},
							{
								"__op" : "get_next_pc",
								"_mm" : "pointer"
							},
							{
								"__op" : "real_address",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "ref_lab",
										"_mm" : "pointer",
										"_name" : "_1"
									}
								]
							}
						]
					}
				]
			},
			{
				"__iop" : "st",
				"_mm" : "s64",
				"args" : 
				[
					{
						"__op" : "binop",
						"_binop" : "add",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "arr_data_address",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "deref",
										"_mm" : "pointer",
										"args" : 
										[
											{
												"__op" : "ref_sym",
												"_mm" : "pointer",
												"_name" : "arr"
											}
										]
									}
								]
							},
							{
								"__op" : "binop",
								"_binop" : "mul",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "const",
										"_immediate" : "8",
										"_mm" : "length"
									},
									{
										"__op" : "ld",
										"_mm" : "u64",
										"args" : 
										[
											{
												"__op" : "real_address",
												"_mm" : "pointer",
												"args" : 
												[
													{
														"__op" : "ref_sym",
														"_mm" : "pointer",
														"_name" : "i"
													}
												]
											}
										]
									}
								]
							}
						]
					},
					{
						"__op" : "binop",
						"_binop" : "add",
						"_mm" : "s64",
						"args" : 
						[
							{
								"__op" : "ld",
								"_mm" : "s64",
								"args" : 
								[
									{
										"__op" : "binop",
										"_binop" : "add",
										"_mm" : "pointer",
										"args" : 
										[
											{
												"__op" : "arr_data_address",
												"_mm" : "pointer",
												"args" : 
												[
													{
														"__op" : "deref",
														"_mm" : "pointer",
														"args" : 
														[
															{
																"__op" : "ref_sym",
																"_mm" : "pointer",
																"_name" : "arr"
															}
														]
													}
												]
											},
											{
												"__op" : "binop",
												"_binop" : "mul",
												"_mm" : "pointer",
												"args" : 
												[
													{
														"__op" : "const",
														"_immediate" : "8",
														"_mm" : "length"
													},
													{
														"__op" : "ld",
														"_mm" : "u64",
														"args" : 
														[
															{
																"__op" : "real_address",
																"_mm" : "pointer",
																"args" : 
																[
																	{
																		"__op" : "ref_sym",
																		"_mm" : "pointer",
																		"_name" : "i"
																	}
																]
															}
														]
													}
												]
											}
										]
									}
								]
							},
							{
								"__op" : "ld",
								"_mm" : "s64",
								"args" : 
								[
									{
										"__op" : "binop",
										"_binop" : "add",
										"_mm" : "pointer",
										"args" : 
										[
											{
												"__op" : "arr_data_address",
												"_mm" : "pointer",
												"args" : 
												[
													{
														"__op" : "deref",
														"_mm" : "pointer",
														"args" : 
														[
															{
																"__op" : "ref_sym",
																"_mm" : "pointer",
																"_name" : "arr"
															}
														]
													}
												]
											},
											{
												"__op" : "binop",
												"_binop" : "mul",
												"_mm" : "pointer",
												"args" : 
												[
													{
														"__op" : "const",
														"_immediate" : "8",
														"_mm" : "length"
													},
													{
														"__op" : "ld",
														"_mm" : "u64",
														"args" : 
														[
															{
																"__op" : "real_address",
																"_mm" : "pointer",
																"args" : 
																[
																	{
																		"__op" : "ref_sym",
																		"_mm" : "pointer",
																		"_name" : "i"
																	}
																]
															}
														]
													}
												]
											}
										]
									}
								]
							}
						]
					}
				]
			},
			{
				"__iop" : "st",
				"_mm" : "u64",
				"args" : 
				[
					{
						"__op" : "real_address",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "i"
							}
						]
					},
					{
						"__op" : "binop",
						"_binop" : "add",
						"_mm" : "u64",
						"args" : 
						[
							{
								"__op" : "ld",
								"_mm" : "u64",
								"args" : 
								[
									{
										"__op" : "real_address",
										"_mm" : "pointer",
										"args" : 
										[
											{
												"__op" : "ref_sym",
												"_mm" : "pointer",
												"_name" : "i"
											}
										]
									}
								]
							},
							{
								"__op" : "const",
								"_immediate" : "1",
								"_mm" : "s64"
							}
						]
					}
				]
			},
			{
				"__iop" : "jump",
				"args" : 
				[
					{
						"__op" : "ref_lab",
						"_mm" : "pointer",
						"_name" : "_0"
					}
				]
			},
			{
				"__iop" : "label",
				"_name" : "_1"
			}
		]
	},
	{
		"_func_name" : "disp_arr_s64",
		"contents" : 
		[
			{
				"__iop" : "st",
				"_mm" : "u64",
				"args" : 
				[
					{
						"__op" : "real_address",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "i"
							}
						]
					},
					{
						"__op" : "const",
						"_immediate" : "0",
						"_mm" : "s64"
					}
				]
			},
			{
				"__iop" : "label",
				"_name" : "_0"
			},
			{
				"__iop" : "jump",
				"args" : 
				[
					{
						"__op" : "if_then_else",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "binop",
								"_binop" : "cmp_lt",
								"_mm" : "u64",
								"args" : 
								[
									{
										"__op" : "ld",
										"_mm" : "u64",
										"args" : 
										[
											{
												"__op" : "real_address",
												"_mm" : "pointer",
												"args" : 
												[
													{
														"__op" : "ref_sym",
														"_mm" : "pointer",
														"_name" : "i"
													}
												]
											}
										]
									},
									{
										"__op" : "len",
										"_mm" : "length",
										"args" : 
										[
											{
												"__op" : "ref_sym",
												"_mm" : "pointer",
												"_name" : "arr"
											}
										]
									}
								]
							},
							{
								"__op" : "get_next_pc",
								"_mm" : "pointer"
							},
							{
								"__op" : "real_address",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "ref_lab",
										"_mm" : "pointer",
										"_name" : "_1"
									}
								]
							}
						]
					}
				]
			},
			{
				"__iop" : "syscall",
				"_syscall_shorthand_op" : "disp_num",
				"args" : 
				[
					{
						"__op" : "ld",
						"_mm" : "s64",
						"args" : 
						[
							{
								"__op" : "binop",
								"_binop" : "add",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "arr_data_address",
										"_mm" : "pointer",
										"args" : 
										[
											{
												"__op" : "deref",
												"_mm" : "pointer",
												"args" : 
												[
													{
														"__op" : "ref_sym",
														"_mm" : "pointer",
														"_name" : "arr"
													}
												]
											}
										]
									},
									{
										"__op" : "binop",
										"_binop" : "mul",
										"_mm" : "pointer",
										"args" : 
										[
											{
												"__op" : "const",
												"_immediate" : "8",
												"_mm" : "length"
											},
											{
												"__op" : "ld",
												"_mm" : "u64",
												"args" : 
												[
													{
														"__op" : "real_address",
														"_mm" : "pointer",
														"args" : 
														[
															{
																"__op" : "ref_sym",
																"_mm" : "pointer",
																"_name" : "i"
															}
														]
													}
												]
											}
										]
									}
								]
							}
						]
					}
				]
			},
			{
				"__iop" : "st",
				"_mm" : "u64",
				"args" : 
				[
					{
						"__op" : "real_address",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "i"
							}
						]
					},
					{
						"__op" : "binop",
						"_binop" : "add",
						"_mm" : "u64",
						"args" : 
						[
							{
								"__op" : "ld",
								"_mm" : "u64",
								"args" : 
								[
									{
										"__op" : "real_address",
										"_mm" : "pointer",
										"args" : 
										[
											{
												"__op" : "ref_sym",
												"_mm" : "pointer",
												"_name" : "i"
											}
										]
									}
								]
							},
							{
								"__op" : "const",
								"_immediate" : "1",
								"_mm" : "s64"
							}
						]
					}
				]
			},
			{
				"__iop" : "jump",
				"args" : 
				[
					{
						"__op" : "if_then_else",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "binop",
								"_binop" : "cmp_lt",
								"_mm" : "u64",
								"args" : 
								[
									{
										"__op" : "ld",
										"_mm" : "u64",
										"args" : 
										[
											{
												"__op" : "real_address",
												"_mm" : "pointer",
												"args" : 
												[
													{
														"__op" : "ref_sym",
														"_mm" : "pointer",
														"_name" : "i"
													}
												]
											}
										]
									},
									{
										"__op" : "len",
										"_mm" : "length",
										"args" : 
										[
											{
												"__op" : "ref_sym",
												"_mm" : "pointer",
												"_name" : "arr"
											}
										]
									}
								]
							},
							{
								"__op" : "get_next_pc",
								"_mm" : "pointer"
							},
							{
								"__op" : "real_address",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "ref_lab",
										"_mm" : "pointer",
										"_name" : "_2"
									}
								]
							}
						]
					}
				]
			},
			{
				"__iop" : "call",
				"args" : 
				[
					{
						"__op" : "call_with_ret",
						"_mm" : "u8",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "disp_comma"
							}
						]
					}
				]
			},
			{
				"__iop" : "call",
				"args" : 
				[
					{
						"__op" : "call_with_ret",
						"_mm" : "u8",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "disp_space"
							}
						]
					}
				]
			},
			{
				"__iop" : "label",
				"_name" : "_2"
			},
			{
				"__iop" : "jump",
				"args" : 
				[
					{
						"__op" : "ref_lab",
						"_mm" : "pointer",
						"_name" : "_0"
					}
				]
			},
			{
				"__iop" : "label",
				"_name" : "_1"
			},
			{
				"__iop" : "call",
				"args" : 
				[
					{
						"__op" : "call_with_ret",
						"_mm" : "u8",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "disp_newline"
							}
						]
					}
				]
			},
			{
				"__iop" : "return_expr",
				"args" : 
				[
					{
						"__op" : "sizeof",
						"_mm" : "length",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "arr"
							}
						]
					}
				]
			}
		]
	},
	{
		"_func_name" : "get_size_s64",
		"contents" : 
		[
			{
				"__iop" : "return_expr",
				"args" : 
				[
					{
						"__op" : "sizeof",
						"_mm" : "length",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "a"
							}
						]
					}
				]
			}
		]
	},
	{
		"_func_name" : "clear_arr_s64",
		"contents" : 
		[
			{
				"__iop" : "st",
				"_mm" : "u64",
				"args" : 
				[
					{
						"__op" : "real_address",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "i"
							}
						]
					},
					{
						"__op" : "const",
						"_immediate" : "0",
						"_mm" : "s64"
					}
				]
			},
			{
				"__iop" : "label",
				"_name" : "_0"
			},
			{
				"__iop" : "jump",
				"args" : 
				[
					{
						"__op" : "if_then_else",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "binop",
								"_binop" : "cmp_lt",
								"_mm" : "u64",
								"args" : 
								[
									{
										"__op" : "ld",
										"_mm" : "u64",
										"args" : 
										[
											{
												"__op" : "real_address",
												"_mm" : "pointer",
												"args" : 
												[
													{
														"__op" : "ref_sym",
														"_mm" : "pointer",
														"_name" : "i"
													}
												]
											}
										]
									},
									{
										"__op" : "len",
										"_mm" : "length",
										"args" : 
										[
											{
												"__op" : "ref_sym",
												"_mm" : "pointer",
												"_name" : "to_clear"
											}
										]
									}
								]
							},
							{
								"__op" : "get_next_pc",
								"_mm" : "pointer"
							},
							{
								"__op" : "real_address",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "ref_lab",
										"_mm" : "pointer",
										"_name" : "_1"
									}
								]
							}
						]
					}
				]
			},
			{
				"__iop" : "st",
				"_mm" : "s64",
				"args" : 
				[
					{
						"__op" : "binop",
						"_binop" : "add",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "arr_data_address",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "deref",
										"_mm" : "pointer",
										"args" : 
										[
											{
												"__op" : "ref_sym",
												"_mm" : "pointer",
												"_name" : "to_clear"
											}
										]
									}
								]
							},
							{
								"__op" : "binop",
								"_binop" : "mul",
								"_mm" : "pointer",
								"args" : 
								[
									{
										"__op" : "const",
										"_immediate" : "8",
										"_mm" : "length"
									},
									{
										"__op" : "ld",
										"_mm" : "u64",
										"args" : 
										[
											{
												"__op" : "real_address",
												"_mm" : "pointer",
												"args" : 
												[
													{
														"__op" : "ref_sym",
														"_mm" : "pointer",
														"_name" : "i"
													}
												]
											}
										]
									}
								]
							}
						]
					},
					{
						"__op" : "const",
						"_immediate" : "0",
						"_mm" : "s64"
					}
				]
			},
			{
				"__iop" : "st",
				"_mm" : "u64",
				"args" : 
				[
					{
						"__op" : "real_address",
						"_mm" : "pointer",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "i"
							}
						]
					},
					{
						"__op" : "binop",
						"_binop" : "add",
						"_mm" : "u64",
						"args" : 
						[
							{
								"__op" : "ld",
								"_mm" : "u64",
								"args" : 
								[
									{
										"__op" : "real_address",
										"_mm" : "pointer",
										"args" : 
										[
											{
												"__op" : "ref_sym",
												"_mm" : "pointer",
												"_name" : "i"
											}
										]
									}
								]
							},
							{
								"__op" : "const",
								"_immediate" : "1",
								"_mm" : "s64"
							}
						]
					}
				]
			},
			{
				"__iop" : "jump",
				"args" : 
				[
					{
						"__op" : "ref_lab",
						"_mm" : "pointer",
						"_name" : "_0"
					}
				]
			},
			{
				"__iop" : "label",
				"_name" : "_1"
			},
			{
				"__iop" : "return_expr",
				"args" : 
				[
					{
						"__op" : "sizeof",
						"_mm" : "length",
						"args" : 
						[
							{
								"__op" : "ref_sym",
								"_mm" : "pointer",
								"_name" : "to_clear"
							}
						]
					}
				]
			}
		]
	}
]
